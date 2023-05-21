#ifndef COPY_TO_VECTOR_H
#define COPY_TO_VECTOR_H

#include "io/streams.h"
#include "util.h"

std::vector<Datum> copy_to_vector(io::InputStream& input);

#endif