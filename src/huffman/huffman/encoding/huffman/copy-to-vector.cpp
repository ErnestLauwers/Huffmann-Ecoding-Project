#include <vector>
#include "util.h"
#include "io/memory-buffer.h"
#include "copy-to-vector.h"

std::vector<Datum> copy_to_vector(io::InputStream& input)
{
	std::vector<Datum> result;
	while (!input.end_reached()) {
		result.push_back(input.read());
	}
	return result;
}