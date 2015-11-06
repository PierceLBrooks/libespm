/*
 * This file is part of libespm2
 *
 * Copyright (C) 2015 Oliver Hamlet
 *
 * libespm2 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libespm2 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libespm2. If not, see <http://www.gnu.org/licenses/>.
 */

#include <string>
#include <fstream>

#include <boost/filesystem.hpp>

namespace libespm2 {

  class SkyrimPlugin {
    private:
    std::string name;

    public:
    inline void load(const boost::filesystem::path& filepath) {

      std::ifstream input(filepath.string(), std::ios::binary);
      if (!input.good())
        throw std::runtime_error("Cannot open plugin file at " + filepath.string());

      name = filepath.filename().string();
    }

    inline std::string getName() const {
      return name;
    }
  };
}
