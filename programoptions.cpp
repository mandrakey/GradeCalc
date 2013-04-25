#include "programoptions.h"

//==============================================================================
// Implementation of ProgramOptions

//----
// Initialize static members
QHash<QString, QVariant> ProgramOptions::mRecognized = QHash<QString, QVariant>();
QStringList ProgramOptions::mPositionals = QStringList();
QStringList ProgramOptions::mUnrecognized = QStringList();

QList<ProgramOptions::Option> ProgramOptions::mAddedOptions = QList<ProgramOptions::Option>();

po::options_description ProgramOptions::mRecognizedOptions;
po::positional_options_description ProgramOptions::mPositionalOptions;

ProgramOptions::ProgramOptions()
{
}

ProgramOptions::const_iterator ProgramOptions::begin() const
{
    return const_iterator(this, ProgramOptions::const_iterator::START);
}

ProgramOptions::const_iterator ProgramOptions::end() const
{
    return const_iterator(this, ProgramOptions::const_iterator::END);
}

void ProgramOptions::parse(int argc, char *argv[])
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

bool ProgramOptions::contains(const Option &o) const
{
    return mAddedOptions.contains(o);
}

bool ProgramOptions::contains(const QString &name) const
{
    foreach (Option o, mAddedOptions) {
        if (o.name().compare(name) == 0) {
            return true;
        }
    }

    return false;
}

bool ProgramOptions::recognized(const Option &o) const
{
    return mRecognized.keys().contains(o.name());
}

bool ProgramOptions::recognized(const QString &name) const
{
    return mRecognized.keys().contains(name);
}

QVariant ProgramOptions::recognizedValue(const Option &o) const
{
    return mRecognized.value(o.name());
}

QVariant ProgramOptions::recognizedValue(const QString &name) const
{
    return mRecognized.value(name);
}

void ProgramOptions::printHelp() const
{
    std::cout << *this;
}

QHash<QString, QVariant>& ProgramOptions::recognized() const
{
    return mRecognized;
}

QList<QString>& ProgramOptions::positionals() const
{
    return mPositionals;
}

QList<QString>& ProgramOptions::unrecognized() const
{
    return mUnrecognized;
}

ProgramOptions& ProgramOptions::operator<<(const Option& o)
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

void ProgramOptions::addOption(QVariant::Type type, const char *name,
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

void ProgramOptions::addPositional(const char *name,
                                   bool positional, int maxCount)
{
    if (positional) {
        if (maxCount > 1) {
            maxCount--;
        }
        mPositionalOptions.add(name, maxCount);
    }
}

std::ostream& operator<<(std::ostream& lhs, const ProgramOptions& rhs)
{
    rhs.mRecognizedOptions.print(lhs);
    return lhs;
}

//==============================================================================
// Implementation of Option

ProgramOptions::Option::Option(const QString &name, const QString &alias,
                               const QString &description,
                               const QVariant &defaultValue,
                               bool positional, int maxCount) :
    mType(QVariant::Invalid), mName(name), mAlias(alias),
    mDescription(description), mDefaultValue(defaultValue),
    mPositional(positional), mMaxCount(maxCount)
{
}

ProgramOptions::Option::Option(const QVariant::Type type, const QString &name,
                               const QString &alias, const QString &description,
                               const QVariant &defaultValue,
                               bool positional, int maxCount) :
    mType(type), mName(name), mAlias(alias), mDescription(description),
    mDefaultValue(defaultValue), mPositional(positional), mMaxCount(maxCount)
{
}

bool ProgramOptions::Option::operator==(const Option& other) const
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

QVariant::Type ProgramOptions::Option::type() const
{
    return mType;
}

QString ProgramOptions::Option::name() const
{
    return mName;
}

QString ProgramOptions::Option::alias() const
{
    return mAlias;
}

QString ProgramOptions::Option::description() const
{
    return mDescription;
}

QVariant ProgramOptions::Option::defaultValue() const
{
    return mDefaultValue;
}

bool ProgramOptions::Option::positional() const
{
    return mPositional;
}

int ProgramOptions::Option::maxCount() const
{
    return mMaxCount;
}

std::ostream& operator<<(std::ostream& out, const ProgramOptions::Option& o)
{
    out << o.mName.toStdString();
    return out;
}

//==============================================================================
// Implementation of ProgramOptions::const_iterator

ProgramOptions::const_iterator::const_iterator(const ProgramOptions *_v,
                                               etype t) :
    mIndex(0), mKeys(QList<QString>()), mObject(0)
{
    Q_ASSERT(_v);
    mObject = _v;

    mKeys = mObject->recognized().keys();
    mIndex = (t == START) ? 0 : mKeys.size() - 1;
}

const QVariant ProgramOptions::const_iterator::operator *()
{
    return mObject->recognized().value(mKeys.at(mIndex));
}

bool ProgramOptions::const_iterator::operator !=(const const_iterator& it) const
{
    return (mKeys.at(mIndex).compare(it.mKeys.at(it.mIndex)));
}

ProgramOptions::const_iterator& ProgramOptions::const_iterator::operator ++()
{
    ++mIndex;
    return *this;
}


