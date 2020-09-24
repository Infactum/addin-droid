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

#ifndef DROIDADDIN_H
#define DROIDADDIN_H

#include "Component.h"
#include "IAndroid.h"

class DroidAddIn : public Component {
public:
    DroidAddIn();

private:
    std::string extensionName() override { return "Droid"; };

    void addFilter(const variant_t &action);

    void clearFilters();

    void registerReceiver();

    void unregisterReceiver();

    void initExtension();

    std::unique_ptr<IAndroid> ext;
    std::string error_info;
};


#endif //DROIDADDIN_H
