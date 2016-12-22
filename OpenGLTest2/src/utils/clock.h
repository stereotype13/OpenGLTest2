#pragma once
#include <vector>
#include <chrono>

namespace VR {
	namespace utils {

		typedef std::chrono::high_resolution_clock HighResolutionClock;
		typedef std::chrono::duration<float, std::milli> milliseconds_type;

		class Clock {
		public:
			class ClockListener {
			public:
				virtual void onTick(double delta) = 0;
			};

		private:
			std::vector<ClockListener*> mClockListeners;
			std::chrono::time_point<HighResolutionClock> mStartTimePoint;
			double mDeltaTime = 0.0;
		public:
			void addListener(ClockListener* listener);
			void tick();
		};
	}
}
