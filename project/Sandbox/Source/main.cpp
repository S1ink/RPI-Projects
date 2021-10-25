#include <atomic>
#include <iostream>
#include <thread>

#include "resources.h"
#include "output.h"
#include "timing.h"
#include "program.h"

CE_STR t_red = "\033[38;2;255;0;0m";
CE_STR t_orange = "\033[38;2;255;100;0m";
CE_STR t_yellow = "\033[38;2;240;240;0m";
CE_STR t_green = "\033[38;2;0;255;0m";
CE_STR t_blue = "\033[38;2;50;50;255m";
CE_STR t_purple = "\033[38;2;150;0;255m";
CE_STR t_reset = "\033[0m";

std::atomic_bool run = { true };
StopWatch runtime("Runtime", &std::cout, 0);
//std::atomic_bool run2 = { true };

//static void endCondition() {
//	std::cin.ignore();
//	run = false;
//	/*std::cin.ignore();
//	run2 = false;*/
//}

//static void callback(int gpio, int level, uint32_t tick) {
//	return;
//}

//lstream logger;

void inline wait(uint seconds) {
	std::this_thread::sleep_for(CHRONO::seconds(seconds));
}
void inline mwait(uint milliseconds) {
	std::this_thread::sleep_for(CHRONO::milliseconds(milliseconds));
}
void inline uwait(uint microseconds) {
	std::this_thread::sleep_for(CHRONO::microseconds(microseconds));
}
void inline nwait(uint nanoseconds) {
	std::this_thread::sleep_for(CHRONO::nanoseconds(nanoseconds));
}

void on_exit() {
	runtime.end();
}

//int of_exec(const char* command, lstream& output) {
//	FILE* pipe = popen(command, "r");
//	if (!pipe) {
//		output.openOutput();
//		output << "popen function failed";
//		output.close();
//	}
//	else {
//		char buffer[128];
//		while (fgets(buffer, 128, pipe) != NULL) {
//			output.openOutput();
//			output << buffer;
//			output.close();
//		}
//	}
//	return pclose(pipe);
//}

void visualUtilization(float utilization) {
	if (utilization >= 80.f) {
		std::cout << t_red;
	}
	else if (utilization >= 50.f) {
		std::cout << t_orange;
	}
	else if (utilization >= 20.f) {
		std::cout << t_yellow;
	}
	else {
		std::cout << t_green;
	}
}

//std::string matchBest(std::string target, std::vector<std::string> list) {
//	std::vector<uint> matches;
//	for (uint i = 0; i < list.size(); i++) {
//		if (!target.compare(0, target.size(), list[i].substr(0, target.size()))) {
//			matches.emplace_back(i);
//		}
//	}
//	if (matches.size() >= 1) {
//		return list[matches[0]];
//	}
//	else {
//		while (matches.size() == 0) {
//			uint j = 1;
//			for (uint i = 0; i < list.size(); i++) {
//				if (target.compare(0, target.size() - j, list[i].substr(0, target.size() - j))) {
//					matches.emplace_back(i);
//				}
//			}
//			j++;
//			if (target.size() - j < 1) {
//				break;
//			}
//		}
//	}
//}

//class M_Base {
//public:
//	class C_Base {
//	protected:
//		M_Base* env;
//		
//		olstream* getBaseStream() {
//			return &(this->env->stream);
//		}
//	public:
//		virtual void init(M_Base* outer) {
//			this->env = outer;
//		}
//		virtual void print(const char* message) {
//			this->env->stream << "C_BASE: " << message << newline;
//		}
//	};
//
//	M_Base(const olstream& stream) : stream(stream) {}
//	M_Base(olstream&& stream) : stream(stream) {}
//
//	virtual void t_print(const char* message) = 0;
//private:
//	olstream stream;
//};
//
//template<typename cont_t = M_Base::C_Base>
//class M_Test : public M_Base {
//public:
//	M_Test(const olstream& stream, const C_Base& cont = C_Base()) : M_Base(stream) {
//		this->container = static_cast<const cont_t&>(cont);
//		this->container.init(this);
//	}
//	M_Test(olstream&& stream, const C_Base& cont = C_Base()) : M_Base(stream) {
//		this->container = static_cast<const cont_t&>(cont);
//		this->container.init(this);
//	}
//
//	void t_print(const char* message) override {
//		this->container.print(message);
//	}
//private:
//	cont_t container;
//};
//
//class C_Test : public M_Base::C_Base {
//public:
//	void print(const char* message) override {
//		this->getBaseStream()->operator<<("C_TEST(!!!!): ") << message << newline;
//	}
//};
//
//class Random : public M_Base::C_Base {
//public:
//	void print(const char* message) override {
//		this->getBaseStream()->operator<<("Just made this on the fly bro, heres the message - ") << message << newline;
//	}
//};

std::atomic_bool thr = { true };

int main(int argc, char* argv[], char* envp[]) {
	runtime.setStart();
	progdir.setDir(argv[0]);
	//std::thread end(endCondition);
	
	atexit(on_exit);
	//sig_handle.setadv();	//update sighandle
	//sig_handle.setLog("/data/server.txt");

	olstream s1;
	olstream s2;

	//std::cout << strlen(nullptr) << newline;

	std::cout << safeNull(s1.getPath()) << " : " << safeLen(s1.getPath()) << newline 
		<< safeNull(s2.getPath()) << " : " << safeLen(s2.getPath()) << "\n\n";
	//std::cout << "about to copy\n";

	s2 = s1;
	std::cout << safeNull(s1.getPath()) << " : " << safeLen(s1.getPath()) << newline
		<< safeNull(s2.getPath()) << " : " << safeLen(s2.getPath()) << "\n\n";

	s1 = olstream("NEW PATH");
	std::cout << safeNull(s1.getPath()) << " : " << safeLen(s1.getPath()) << newline
		<< safeNull(s2.getPath()) << " : " << safeLen(s2.getPath()) << "\n\n";

	s2.setStream("ANOTHER NEW PATH");
	std::cout << safeNull(s1.getPath()) << " : " << safeLen(s1.getPath()) << newline
		<< safeNull(s2.getPath()) << " : " << safeLen(s2.getPath()) << "\n\n";

	olstream s3(std::move(olstream("/path/to/segv.exe")));
	std::cout << safeNull(s1.getPath()) << " : " << safeLen(s1.getPath()) << newline
		<< safeNull(s2.getPath()) << " : " << safeLen(s2.getPath()) << newline
		<< safeNull(s3.getPath()) << " : " << safeLen(s3.getPath()) << "\n\n";

	//std::cout << word << newline;

	//std::thread main(outer1, &std::cout);
	
	//std::this_thread::sleep_for(CHRONO::seconds(30));
	//thr = false;

	//main.join();

	//http::HttpServer server(&std::cout, nullptr, http::Version::HTTP_1_1, "/data/pihost/resources");
	//server.serve();

	/*CPU& cpustat = CPU::get();	
	while (1) {
		std::vector<float> utilization = cpustat.fromReference();
		visualUtilization(utilization[0]);
		std::cout << "Total: " << t_reset << utilization[0] << "%\n";
		for (uint i = 1; i < utilization.size(); i++) {
			visualUtilization(utilization[i]);
			std::cout << "Core " << i << ": " << t_reset << utilization[i] << "%\n";
		}
		mwait(1000);
		std::cout << "\x1b[5A";
		std::cout << "                    \n                            \n                            \n                              \n                          \n";
		std::cout << "\x1b[5A";
	}*/

	//std::cout << t_red << "red\n";
	//std::cout << t_orange << "orange\n";
	//std::cout << t_yellow << "yellow\n";
	//std::cout << t_green << "green\n";
	//std::cout << t_blue << "blue\n";
	//std::cout << t_purple << "purple\n" << t_reset;

	//end.join();
	return 0;
}

//SIGNALS
/*
9 - KILL >>>>>>>>>>>>>>>>>>>> {unblockable}
19 - Stop >>>>>>>>>>>>>>>>>>> {unblockable}

Handle/Ignore/Log: 
1 - Hangup
5 - Trace trap
13 - Broken pipe
17 - Child status has changed
18 - Continue
20 - Keyboard stop
21 - Backround read from "tty"
22 - Backround write to "tty"
23 - Urgent condition on socket
28 - Window size change
29 - IO now possible
31 - Bad system call

Exit:
2 - Interrupt
3 - Quit
4 - Illegal instruction *
6 - Abort
7 - Bus error **
8 - FPAE
11 - Segmentation violation
15 - Termination
16 - Stack fault *
24 - CPU limit exceeded *
25 - File size limit exceeded *
30 - Power failure restart

Conditional:
10 - user defined
12 - user defined #2
14 - Alarm
26 - Virtual time alarm
27 - Profiling alarm clock

*/

//NOTES

/*while (true) {
		std::string inp;
		std::cout << "Enter a file path to open: ";
		std::cin >> inp;
		if (inp == "exit") {
			break;
		}
		uint size = 0;
		std::string buffer;
		std::fstream file;
		file.open(inp, std::ios::in | std::ios::binary);
		if (!file) {
			std::cout << "File is not readable or does not exist" << newline;
		}
		else {
			file.seekg(0, std::ios::end);
			size = file.tellg();
			buffer.resize(size);
			file.seekg(0, std::ios::beg);
			file.read(&buffer[0], size);
			file.close();
			std::cout << buffer.size() << newline;
			std::cout << buffer << newline;
		}
	}*/