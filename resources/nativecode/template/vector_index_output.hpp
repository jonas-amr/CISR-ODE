
#WARNING_COMMENTS#

// path: ./#TRACING_PATH#

#pragma once

namespace #TITLES#
{
	std::string output_header[]={
		#OUTPUTHEADER#
	};

	#INDEX_NUMBERS_COMMENTS#

	#INDEX_CONSTANTS#

	// ****************************
	// total size of #TITLE# vector

	const int #TITLES#_size=#TOTAL_SIZE#;
	
	//Export list
	const struct FigureList
	{
		std::string file_suffix; // no space is accepted in file suffix name
		int output_index;
	} figure_list[]={
		#FIGURE_LIST#
	};
};
