#ifndef PROGRAMOPTIONS_H
#define PROGRAMOPTIONS_H

#include <boost/program_options.hpp>

#include "exceptions/uninitializedexception.h"

namespace po = boost::program_options;

using std::vector;
using std::string;

class ProgramOptions
{
public:
    explicit ProgramOptions();
    ProgramOptions(int argc, char *argv[]);

    void reload(int argc, char *argv[]);

    po::variables_map& getVariables() const throw (UninitializedException);

    static const string DATAFILE_DEFAULT;
    static const string GRADESFILE_DEFAULT;

private:
    void init();
    void parse(int argc, char *argv[]);

    static bool mInitialized;
    static po::options_description mCmdOptions;
    static po::positional_options_description mCmdPositionals;
    static po::variables_map mVariables;
    static vector<string> mUnrecognized;
};

#endif // PROGRAMOPTIONS_H
