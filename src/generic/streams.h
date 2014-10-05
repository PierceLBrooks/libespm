/*
 * streams.h
 * This file is part of libespm
 *
 * Copyright (C) 2013 WrinklyNinja
 *
 * libespm is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libespm is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libespm. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __ESPM_STREAMS__
#define __ESPM_STREAMS__

#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/device/file_descriptor.hpp>

namespace espm {
    typedef boost::iostreams::stream< boost::iostreams::file_descriptor_sink > ofstream;
    typedef boost::iostreams::stream< boost::iostreams::file_descriptor_source > ifstream;
    typedef boost::iostreams::stream< boost::iostreams::file_descriptor > fstream;
}

#endif
