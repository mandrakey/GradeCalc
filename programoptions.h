#ifndef PROGRAMOPTIONS_H
#define PROGRAMOPTIONS_H

#include <QList>
#include <QStringList>
#include <QHash>
#include <QVariant>
#include <QDebug>

#include <iostream>

#include <boost/program_options.hpp>

namespace po = boost::program_options;

using std::vector;
using std::string;

/**
 * Class to manage program options for any program.
 * Follows the monostate pattern. Only Qt classes necessary for use, boost
 * libs are kept to internal implementation only.
 * @see http://www.boost.org/doc/libs/1_53_0/doc/html/program_options.html
 * @author Maurice Bleuel <mbleuel@bleuelmedia.com>
 * @ingroup lib
 */
class ProgramOptions
{
    friend std::ostream& operator<<(std::ostream&, const ProgramOptions&);
public:
    
    /**
     * Iterator implementation for use with foreach loop.
     */
    class const_iterator
    {
    public:
        enum etype { START, END };

        /** Construct a new const_iterator for a given ProgramOptions instance.
         * @param _v Pointer to ProgramOptions instance to use
         * @param t Type of enumerator (beginning at first or last element)
         */
        const_iterator(const ProgramOptions *_v, etype t);
        
        /**
         * Return the value currently pointed at in recognized list.
         * @return QVariant data at current position
         */
        const QVariant operator*();
        
        /**
         * Check wether this iterator and another one point at the same index.
         * @param other Iterator to check against.
         * @return True if both are pointing at the same index, False 
         * otherwise
         */
        bool operator!=(const const_iterator&) const;
        
        /** Advance the index by one. */
        const_iterator& operator++();

    private:
        /** Current item index. */
        int mIndex;
        
        /** List of keys to iterate through. */
        QList<QString> mKeys;
        
        /** Points to attached ProgramOptions object. */
        const ProgramOptions *mObject;
    };

    /**
     * Contains one single Option for use with program options.
     * All program options have to be typed!
     */
    class Option
    {
        friend std::ostream& operator<<(std::ostream&, const Option&);
    public:
        
        /**
         * Create a new Option without a type.
         * This option will not hold a value, useful for options like 
         * "--help".
         * @param name Name / complete command of the option. Example:
         * "hello" means, option can be set using "--hello".
         * @param alias Alias / short command of the option. Example:
         * "?" means, option can be set using "-?".
         * @param description Description for the help display
         * @param defaultValue QVariant value to use if the option has not
         * been set. Defaults to an Invalid QVariant meaning "no default"
         * @param positional Define this Option to recognize positionals.
         * Defaults to False
         */
        Option(const QString& name, const QString& alias,
               const QString& description,
               const QVariant& defaultValue = QVariant(),
               bool positional = false, int maxCount = -1);

        /**
         * Create a new Option with a typed value.
         * @param name Name / complete command of the option. Example:
         * "hello" means, option can be set using "--hello".
         * @param alias Alias / short command of the option. Example:
         * "?" means, option can be set using "-?".
         * @param description Description for the help display
         * @param defaultValue QVariant value to use if the option has not
         * been set. Defaults to an Invalid QVariant meaning "no default"
         * @param positional Define this Option to recognize positionals.
         * Defaults to False
         * @param maxCount If type of the Option is QVariant::List, this
         * defines the maximum amount of options that can be set (example: only
         * two filenames allowed). Defaults to -1 (unlimited).
         */
        Option(const QVariant::Type type, const QString& name,
               const QString& alias, const QString& description,
               const QVariant& defaultValue = QVariant(),
               bool positional = false, int maxCount = -1);

        /**
         * Check wether this options equals another one.
         * @param other The option to check against
         * @return True if equal
         */
        bool operator==(const Option& other) const;

        //----
        // Getter / Setter

        QVariant::Type type() const;
        QString name() const;
        QString alias() const;
        QString description() const;
        QVariant defaultValue() const;
        bool positional() const;
        int maxCount() const;

    private:
        /**
         * Type of this Option.
         * Possible values:
         * - QVariant::Int
         * - QVariant::Double
         * - QVariant::String
         * - QVariant::List
         */
        QVariant::Type mType;

        /** Name of the Option. */
        QString mName;

        /** Shortname or alias of the Option, if any. */
        QString mAlias;

        /** Description for help text. */
        QString mDescription;

        /** Default value for this option. */
        QVariant mDefaultValue;

        /** Is this option defined as positional. */
        bool mPositional;

        /** Maximum amount of values for this option.*/
        int mMaxCount;
    };

    /**
     * Construct a ProgramOptions instance with access to monostate data.
     */
    ProgramOptions();

    // Iterator interface
    /**
     * Retrieve an iterator pointing to the first recognized value.
     * @return A new iterator
     */
    const_iterator begin() const;

    /**
     * Retrieve an iterator pointing to the last recognized value.
     * @return A new iterator
     */
    const_iterator end() const;

    /**
     * Parse the given commandline options.
     * @param argc
     * @param argv
     */
    void parse(int argc, char* argv[]);

    /** Check wether Option o was added to the recognizable ProgramOptions.
     * @param o Reference to option to check for
     * @return Wether or not the option has been added
     */
    bool contains(const Option& o) const;

    /**
     * Check wether an Option with given name was added.
     * @param name Name of the option to check for
     * @return True if it was added
     */
    bool contains(const QString& name) const;

    /**
     * Check wether the given Option was found when parsing the arguments.
     * @param o The option to search for
     * @return TRUE if option has been recognized
     */
    bool recognized(const Option& o) const;

    /**
     * Check wether the given Option was found when parsing the arguments.
     * @param name Name of the option to check for
     * @return True if recognized
     */
    bool recognized(const QString& name) const;

    QVariant recognizedValue(const Option& o) const;
    QVariant recognizedValue(const QString& name) const;

    /**
     * Print help to standard output cout.
     */
    void printHelp() const;

    // Getter / Setter
    QHash<QString, QVariant>& recognized() const;
    QList<QString>& positionals() const;
    QList<QString>& unrecognized() const;

    // Option handling
    ProgramOptions& operator<<(const Option& o);

private:
    /**
     * Add a new option to the internally used mRecognizedOptions.
     * @param type Type of the Option.
     * @param name
     * @param description
     * @param defaultValue
     * @param positional
     * @param maxCount
     * @see http://www.boost.org/doc/libs/1_53_0/doc/html/program_options/tutorial.html#idp119971568
     */
    void addOption(QVariant::Type type, const char *name,
                   const char *alias, const char *description,
                   const QVariant& defaultValue = QVariant::Invalid,
                   bool positional = false, int maxCount = -1);

    /**
     * Declare a previously set Option as catching positionals.
     * @param name Name of the Option to define as positional
     * @param positional Make this Option positional or not.
     * @param maxCount
     */
    void addPositional(const char *name, bool positional, int maxCount);

    /** Contains recognized options after parsing, key is option name. */
    static QHash<QString, QVariant> mRecognized;

    /** Contains catched positional options as strings. */
    static QStringList mPositionals;

    /** Contains any catched options which were not defined prior to parsing. */
    static QStringList mUnrecognized;

    /** Contains a list of added options for use with contains. */
    static QList<Option> mAddedOptions;

    /** Internal representation of added options ready for parsing. */
    static po::options_description mRecognizedOptions;

    /** Internal representation of declared positional options. */
    static po::positional_options_description mPositionalOptions;
};

/**
 * Prints the help message for the current ProgramOptions data.
 * @param lhs Output stream reference to use
 * @param rhs ProgramOptions instance to print help for
 * @return Output stream reference for chaining
 */
std::ostream& operator<<(std::ostream& lhs, const ProgramOptions& rhs);

#endif // PROGRAMOPTIONS_H
