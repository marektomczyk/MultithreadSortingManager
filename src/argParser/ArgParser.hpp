//============================================================================
// Name        : ArgParser.hpp
// Author      : Marek Tomczyk
// Version     : 1.0
// Copyright   : Copyright (C) 2019 Marek Tomczyk. All rights reserved.
// Description : CXXOPTS wrapper class
//============================================================================

#ifndef _ARGPARSER_HPP_
#define _ARGPARSER_HPP_

#include "cxxopts.hpp"

class ArgParser
{
public:
	/// @brief Parsing errors enum class
	enum class eParseResult
	{
		PARSE_OK,
		REQUIRED_PARAM_NOT_GIVEN_ERR,
		CXXOPTS_PARSE_ERR
	};

	/// @brief Get singleton instance method
	static ArgParser & GetInstance()
	{
		static ArgParser instance;
		return instance;
	}

	/// @brief Parse input arguments
	eParseResult ParseArguments(int argc, char* argv[])
	{
		eParseResult res = eParseResult::PARSE_OK;
		try
		{
			createOptions(argc, argv);
			
			if ( m_options != nullptr )
			{
				auto result = m_options->parse(argc, argv);
				if ( result.count("h") )
				{
					m_showHelp = true;
					return res;
				}

				if ( result.count("i") )
				{
					m_inputFileName = result["i"].as<std::string>();
				}
				else
				{
					return eParseResult::REQUIRED_PARAM_NOT_GIVEN_ERR;
				}

				if ( result.count("o") )
				{
					m_outputFileName = result["o"].as<std::string>();
				}
				else
				{
					return eParseResult::REQUIRED_PARAM_NOT_GIVEN_ERR;
				}

				if ( result.count("a") == 0 && result.count("c") == 0 )
				{
					return eParseResult::REQUIRED_PARAM_NOT_GIVEN_ERR;
				}

				if ( result.count("t") )
				{
					m_threadCount = result["t"].as<unsigned int>();
				}

				if ( result.count("l") )
				{
					m_logFileName = result["l"].as<std::string>();
				}

				if ( result.count("a") )
				{
					m_sortAlgorithmName = result["a"].as<std::string>();
				}

				if ( result.count("c") )
				{
					m_withComparison = true;
				}

				if ( result.count("v") )
				{
					m_verifyAfterSort = true;
				}
			}
		}
		catch (const cxxopts::OptionException& ex)
		{
			res = eParseResult::CXXOPTS_PARSE_ERR;
		}

		return res;
	}

	/// @brief Get help description
	std::string GetHelp()
	{
		std::string helpStr = "";

		if ( m_options != nullptr )
		{
			helpStr = m_options->help();
		}

		return helpStr;
	}

	/// @brief Getters
	inline std::string  GetInputFileName()       const { return m_inputFileName;     }
	inline std::string  GetOutputFileName()      const { return m_outputFileName;    }
	inline std::string  GetLogFileName()         const { return m_logFileName;       }
	inline std::string  GetSortAlgorithmName()   const { return m_sortAlgorithmName; }
	inline unsigned int GetThreadCount()         const { return m_threadCount;       }
	inline bool         IsWithComparison()       const { return m_withComparison;    }
	inline bool         VerifyAfterSortEnabled() const { return m_verifyAfterSort;   }
	inline bool         ShowHelpRequest()        const { return m_showHelp;          }

private:
	/// @brief Class default constructor
	ArgParser() 
		: m_options( nullptr ),
		  m_threadCount( 1u ),
		  m_withComparison( false ),
	    m_verifyAfterSort( false ) { }

	/// @brief Class destructor
	~ArgParser() 
	{
		delete m_options;
	}

	/// @brief Create cxxopts::Options object
	void createOptions(int argc, char * argv[])
	{
		if ( m_options != nullptr )
			delete m_options;

		m_options = new cxxopts::Options(argv[0]);
		if ( m_options != nullptr )
		{
			m_options->positional_help("[optional args]")
				         .show_positional_help();
			m_options->allow_unrecognised_options()
				         .add_options()
				         ("i,input", "input file name", cxxopts::value<std::string>())
				         ("o,output", "output file name", cxxopts::value<std::string>())
				         ("t,thread", "count of threads", cxxopts::value<unsigned int>()->default_value("1"))
				         ("l,log", "log output file name", cxxopts::value<std::string>())
				         ("a,algorithm", "sort algorithm name", cxxopts::value<std::string>())
				         ("c,comparison", "run all sort algorithm with comparison", cxxopts::value<bool>()->default_value("false"))
				         ("v,verify", "verify if output file is sorted properly", cxxopts::value<bool>()->default_value("false"))
				         ("h,help", "show this help");
		}
	}

	/// @brief Class private members
	cxxopts::Options * m_options;

	std::string        m_inputFileName;
	std::string        m_outputFileName;
	std::string        m_logFileName;
	std::string        m_sortAlgorithmName;
	unsigned int       m_threadCount;
	bool               m_withComparison;
	bool               m_verifyAfterSort;
	bool               m_showHelp;
};

#endif