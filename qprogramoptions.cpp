/* Copyright (C) 2013  Maurice Bleuel (mandrakey@lavabit.com)
 *
 * QProgramOptions is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * QProgramOptions is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QProgramOptions.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "qprogramoptions.h"

//==============================================================================
// Implementation of QProgramOptions

//----
// Initialize static members
QHash<QString, QVariant> QProgramOptions::mRecognized = QHash<QString, QVariant>();
QStringList QProgramOptions::mPositionals = QStringList();
QStringList QProgramOptions::mUnrecognized = QStringList();

QList<QProgramOptions::Option> QProgramOptions::mAddedOptions = QList<QProgramOptions::Option>();

po::options_description QProgramOptions::mRecognizedOptions;
po::positional_options_description QProgramOptions::mPositionalOptions;

QProgramOptions::QProgramOptions()
{
}

QProgramOptions::const_iterator QProgramOptions::begin() const
{
    return const_iterator(this, QProgramOptions::const_iterator::START);
}

QProgramOptions::const_iterator QProgramOptions::end() const
{
    return const_iterator(this, QProgramOptions::const_iterator::END);
}

void QProgramOptions::parse(int argc, char *argv[])
{
    Q_ASSERT(argv);

    try {
    po::parsed_options parsed = po::command_line_parser(argc, argv)
            .options(mRecognizedOptions).positional(mPositionalOptions)
            .allow_unregistered().run();

    po::variables_map variables;
    po::store(parsed, variables);
    po::notify(variables);

    // Parse recognized into QHash
    mRecognized.clear();
    for (po::variables_map::iterator i = variables.begin();
            i != variables.end(); ++i) {

        const po::variable_value& v = i->second;
        const std::type_info& type = v.value().type();
        QString name = QString(i->first.c_str());

        if (type == typeid(int)) {
            mRecognized.insert(name, QVariant(v.as<int>()));
        } else if (type == typeid(double)) {
            mRecognized.insert(name, QVariant(v.as<double>()));
        } else if (type == typeid(std::string)) {
            mRecognized.insert(name, QVariant(QString(v.as<string>().c_str())));
        } else if (type == typeid(bool)) {
            mRecognized.insert(name, QVariant(v.as<bool>()));
        } else if (type == typeid(std::vector<std::string>)) {
            QList<QVariant> l;
            foreach (std::string value, v.as<std::vector<std::string> >()) {
                l << QVariant(value.c_str());
            }
            mRecognized.insert(name, QVariant(l));
        }
    }

    // Save unrecognized in QList
    vector<string> u = po::collect_unrecognized(parsed.options,
                                                po::exclude_positional);
    mUnrecognized.clear();
    foreach (string s, u) {
        mUnrecognized << QString(s.c_str());
    }

    } catch (po::error& e) {
        qDebug() << "Ex: " << e.what();
    }
}

bool QProgramOptions::contains(const Option &o) const
{
    return mAddedOptions.contains(o);
}

bool QProgramOptions::contains(const QString &name) const
{
    foreach (Option o, mAddedOptions) {
        if (o.name().compare(name) == 0) {
            return true;
        }
    }

    return false;
}

bool QProgramOptions::recognized(const Option &o) const
{
    return mRecognized.keys().contains(o.name());
}

bool QProgramOptions::recognized(const QString &name) const
{
    return mRecognized.keys().contains(name);
}

QVariant QProgramOptions::recognizedValue(const Option &o) const
{
    return mRecognized.value(o.name());
}

QVariant QProgramOptions::recognizedValue(const QString &name) const
{
    return mRecognized.value(name);
}

void QProgramOptions::printHelp() const
{
    std::cout << *this;
}

QHash<QString, QVariant>& QProgramOptions::recognized() const
{
    return mRecognized;
}

QList<QString>& QProgramOptions::positionals() const
{
    return mPositionals;
}

QList<QString>& QProgramOptions::unrecognized() const
{
    return mUnrecognized;
}

QProgramOptions& QProgramOptions::operator<<(const Option& o)
{
    addOption(o.type(),
              o.name().toStdString().c_str(),
              o.alias().toStdString().c_str(),
              o.description().toStdString().c_str(),
              o.defaultValue(),
              o.positional(), o.maxCount());

    mAddedOptions << o;
    return *this;
}

void QProgramOptions::addOption(QVariant::Type type, const char *name,
                               const char *alias, const char *description,
                               const QVariant &defaultValue,
                               bool positional, int maxCount)
{
    QVariant dv(defaultValue);
    const char *optionName = (QString(alias).compare("") != 0)
            ? QString("%1,%2").arg(name, alias).toStdString().c_str()
            : name;

    switch (type) {
    case QVariant::Invalid:
    {
        mRecognizedOptions.add_options()
                (optionName, description);
        break;
    }
    case QVariant::Int:
    {
        if (dv.isValid()) {
            mRecognizedOptions.add_options()
                    (optionName, po::value<int>()->default_value(dv.toInt()),
                     description);
        } else {
            mRecognizedOptions.add_options()
                    (optionName, po::value<int>(), description);
        }

        break;
    }
    case QVariant::Double:
    {
        if (dv.isValid()) {
            mRecognizedOptions.add_options()
                    (optionName, po::value<double>()->default_value(dv.toDouble()),
                     description);
        } else {
            mRecognizedOptions.add_options()
                    (optionName, po::value<double>(), description);
        }

        break;
    }
    case QVariant::String:
    {
        if (dv.isValid()) {
            mRecognizedOptions.add_options()
                    (optionName, po::value<std::string>()->default_value(dv.toString().toStdString()),
                     description);
        } else {
            mRecognizedOptions.add_options()
                    (optionName, po::value<std::string>(), description);
        }

        break;
    }
    case QVariant::Bool:
    {
        if (dv.isValid()) {
            mRecognizedOptions.add_options()
                    (optionName, po::value<bool>()->default_value(dv.toBool()),
                     description);
        } else {
            mRecognizedOptions.add_options()
                    (optionName, po::value<bool>(), description);
        }

        break;
    }
    case QVariant::List:
    {
        if (dv.isValid() && dv.toList().size() > 0) {
            std::vector<std::string> v;
            QString vsr;
            foreach (QVariant value, dv.toList()) {
                v.push_back(value.toString().toStdString());
                vsr.append(QString("%1 ").arg(value.toString()));
            }

            mRecognizedOptions.add_options()
                    (optionName,
                     po::value<std::vector<std::string> >()->default_value(v, vsr.trimmed().toStdString().c_str()),
                     description);
        } else {
            mRecognizedOptions.add_options()
                    (optionName,
                     po::value<std::vector<std::string> >(),
                     description);
        }
        break;
    }
    default:
        return;
    }

    addPositional(name, positional, maxCount);
}

void QProgramOptions::addPositional(const char *name,
                                   bool positional, int maxCount)
{
    if (positional) {
        if (maxCount > 1) {
            maxCount--;
        }
        mPositionalOptions.add(name, maxCount);
    }
}

std::ostream& operator<<(std::ostream& lhs, const QProgramOptions& rhs)
{
    rhs.mRecognizedOptions.print(lhs);
    return lhs;
}

//==============================================================================
// Implementation of Option

QProgramOptions::Option::Option(const QString &name, const QString &alias,
                               const QString &description,
                               const QVariant &defaultValue,
                               bool positional, int maxCount) :
    mType(QVariant::Invalid), mName(name), mAlias(alias),
    mDescription(description), mDefaultValue(defaultValue),
    mPositional(positional), mMaxCount(maxCount)
{
}

QProgramOptions::Option::Option(const QVariant::Type type, const QString &name,
                               const QString &alias, const QString &description,
                               const QVariant &defaultValue,
                               bool positional, int maxCount) :
    mType(type), mName(name), mAlias(alias), mDescription(description),
    mDefaultValue(defaultValue), mPositional(positional), mMaxCount(maxCount)
{
}

bool QProgramOptions::Option::operator==(const Option& other) const
{
    if (this->mDefaultValue != other.mDefaultValue
            || this->mDescription.compare(other.mDescription) != 0
            || this->mMaxCount != other.mMaxCount
            || this->mName.compare(other.mName) != 0
            || this->mAlias.compare(other.mAlias) != 0
            || this->mPositional != other.mPositional
            || this->mType != other.mType) {
        return false;
    }

    return true;
}

QVariant::Type QProgramOptions::Option::type() const
{
    return mType;
}

QString QProgramOptions::Option::name() const
{
    return mName;
}

QString QProgramOptions::Option::alias() const
{
    return mAlias;
}

QString QProgramOptions::Option::description() const
{
    return mDescription;
}

QVariant QProgramOptions::Option::defaultValue() const
{
    return mDefaultValue;
}

bool QProgramOptions::Option::positional() const
{
    return mPositional;
}

int QProgramOptions::Option::maxCount() const
{
    return mMaxCount;
}

std::ostream& operator<<(std::ostream& out, const QProgramOptions::Option& o)
{
    out << o.mName.toStdString();
    return out;
}

//==============================================================================
// Implementation of QProgramOptions::const_iterator

QProgramOptions::const_iterator::const_iterator(const QProgramOptions *_v,
                                               etype t) :
    mIndex(0), mKeys(QList<QString>()), mObject(0)
{
    Q_ASSERT(_v);
    mObject = _v;

    mKeys = mObject->recognized().keys();
    mIndex = (t == START) ? 0 : mKeys.size() - 1;
}

const QVariant QProgramOptions::const_iterator::operator *()
{
    return mObject->recognized().value(mKeys.at(mIndex));
}

bool QProgramOptions::const_iterator::operator !=(const const_iterator& it) const
{
    return (mKeys.at(mIndex).compare(it.mKeys.at(it.mIndex)));
}

QProgramOptions::const_iterator& QProgramOptions::const_iterator::operator ++()
{
    ++mIndex;
    return *this;
}


