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

#ifndef ANDROIDCALLBACK_H
#define ANDROIDCALLBACK_H

#include <string>

// Raw pointer to this class is stored inside JVM objects
// Made final instead of interface to prevent multiple virtual inheritance + reinterpret cast trap
class AndroidCallback final {
public:
    typedef std::function<void(std::string, std::string)> EventCallback;

    AndroidCallback(EventCallback ecb) : cb(std::move(ecb)) {}

    void OnEvent(const std::string &msg, const std::string &data) { cb(msg, data); };

private:
    EventCallback cb;
};

#endif //ANDROIDCALLBACK_H
