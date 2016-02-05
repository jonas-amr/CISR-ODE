#pragma once
#include "libs_config.hpp"

namespace config
{
	const uint buffer_size=1000000;
	const uint results_additions=2; // t, dt
	const uint buffer_headers=outputs::outputs_size+config::results_additions;

	const double start_time=0;
	const double stop_time=15;
}


