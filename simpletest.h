#ifndef simpletest_h
#define simpletest_h

#include <iostream>
#include <vector>
#include <algorithm>

namespace simpletest {
	class Reporter {
	public:
		Reporter() : level(0), good(0), bad(0) {}
		virtual void nest(const char* msg) {++level;}
		virtual void unnest() {--level;}
		virtual int getLevel() {return level;}
		virtual void assert(bool ok, const char* msg) {
			if (ok)
				good++;
			else
				bad++;
		}
		virtual void between() {}
		virtual void reportTotals() {}
		bool allOk() {return (bad == 0);}

	protected:
		int		level;
		long	good;
		long	bad;
	};

	class SpecReporter : public Reporter {
	public:
		SpecReporter(std::ostream& stream_) : stream(stream_) {}

		virtual void nest(const char* msg) {
			Reporter::nest(msg);
			indent(getLevel());
			stream << msg << "\n";
		}
		virtual void assert(bool ok, const char* msg) {
			indent(getLevel());
			if (ok) {
				stream << "  - " << msg << "\n";
			}
			else {
				stream << "  X " << msg << "\n";
			}
			Reporter::assert(ok, msg);
		}

		virtual void between() {stream << "\n";}
		virtual void reportTotals() {
			stream << "\n";
			reportCount(good + bad, "complete");
			if (bad > 0) {
				reportCount(bad, "failed");
			}
			stream << "\n";
		}

	private:
		void indent(int level) {
			while (level--) stream << "  ";
		}

		void reportCount(int count, const char* status) {
			stream << "  " << count << (count == 1 ? " test " : " tests ") << status << ".";
		}

		std::ostream& stream;
	};

	class Test {
	public:
		Test() : reporter(NULL) {}
		virtual ~Test() {}
		virtual void execute() = 0;
		void describe(const char* description) {reporter->nest(description);}
		void assert(bool ok, const char* msg = "") {reporter->assert(ok, msg);}
		void setReporter(Reporter& r) {reporter = &r;}

	protected:
		Reporter*	reporter;
	};

	class Suite : public Test {
	public:
		void add(Test* test) {tests.push_back(test);}
		Suite(const char* desc = NULL, Reporter& r = SpecReporter(std::cout)) : description(desc) {setReporter(r);}
		virtual ~Suite() {
			all([] (Test* test) {delete test;});
		}
		void execute() {
			if (description) {
				reporter->between();
				describe(description);
			}
			all([&] (Test* test) {
				int level = reporter->getLevel();
				test->setReporter(*reporter);
				reporter->between();
				test->execute();
				while (reporter->getLevel() > level) reporter->unnest();
			});
		}
		int main() {
			execute();
			reporter->reportTotals();
			return reporter->allOk() ? 0 : 1;
		}

	private:
		template <typename OP> void all(OP op) {
			std::for_each(tests.begin(), tests.end(), op);
		}

		const char*			description;
		std::vector<Test*>	tests;
	};
}

#endif