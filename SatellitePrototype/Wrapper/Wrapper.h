#ifndef TempSolverWrapper_TempSolverWrapper_H
#define TempSolverWrapper_TempSolverWrapper_H

#include <string>

/*
#ifndef TEMP_SOLVER_API
	#define TEMP_SOLVER_API __declspec(dllexport)
#endif
	*/
#ifdef WRAPPER_LIB
#include <msclr/auto_gcroot.h>
	template<class T> struct ManagedHolder
	{
		ManagedHolder()
		{
			m_pObject = gcnew T();
		}
		msclr::auto_gcroot<T^> & object();

		msclr::auto_gcroot<T^> m_pObject;
	};
#endif

class Wrapper
{
	public:
        Wrapper();
        ~Wrapper();
		void createManagedInstances();
		std::string processMessage(const std::string message);
		void processModelTact();
		void processSolversTact();
		void configurate();
	private:
#ifdef WRAPPER_LIB
		ManagedHolder<MProgram::TemporalReasonerX>* pTemporalReasonerHolder;
		ManagedHolder<SolverXLib::SolverX>* pATReasonerHolder;
		ManagedHolder<ModelLib::Model>* pIMHolder;
#endif
		
};

#endif
