/*
 *  addin-droid
 *  Copyright (C) 2020  Infactum
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#ifndef IANDROID_H
#define IANDROID_H

#include <string>

class IAndroid {
public:
    virtual void AddFilter(const std::string &action) = 0;

    virtual void ClearFilters() = 0;

    virtual void Register() = 0;

    virtual void Unregister() = 0;

    virtual ~IAndroid() {};
};

#endif //IANDROID_H
