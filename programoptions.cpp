#include "programoptions.h"

const string ProgramOptions::DATAFILE_DEFAULT = "./data.xml";
const string ProgramOptions::GRADESFILE_DEFAULT = "./lastgrades.xml";

bool ProgramOptions::mInitialized = false;
po::options_description ProgramOptions::mCmdOptions =
        po::options_description("Argumente");
po::positional_options_description ProgramOptions::mCmdPositionals;
po::variables_map ProgramOptions::mVariables;
vector<string> ProgramOptions::mUnrecognized;

void ProgramOptions::init()
{
    mCmdOptions.add_options()
            ("help,?", "show this help")
            ("datafile,d", po::value<string>()->default_value(DATAFILE_DEFAULT),
             "file containing institutions and courses")
            ("gradesfile", po::value<string>()->default_value(GRADESFILE_DEFAULT),
             "load these grade calculations on program start");

    mCmdPositionals.add("gradesfile", 1);
    mInitialized = true;
}

ProgramOptions::ProgramOptions() throw (UninitializedException)
{
    if (!mInitialized)
        throw UninitializedException("ProgramOptions must be initialized first");
}

ProgramOptions::ProgramOptions(int argc, char *argv[])
{
    if (mInitialized)
        return;

    init();
    reload(argc, argv);
}

po::variables_map& ProgramOptions::getVariables() const
{
    return mVariables;
}

void ProgramOptions::reload(int argc, char *argv[])
{
    parse(argc, argv);
}

void ProgramOptions::parse(int argc, char *argv[])
{
    po::parsed_options parsed = po::command_line_parser(argc, argv)
            .options(mCmdOptions).positional(mCmdPositionals)
            .run();

    po::store(parsed, mVariables);
    po::notify(mVariables);
}
