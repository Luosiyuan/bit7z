/*
 * bit7z - A C++ static library to interface with the 7-zip DLLs.
 * Copyright (c) 2014-2021  Riccardo Ostani - All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * Bit7z is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with bit7z; if not, see https://www.gnu.org/licenses/.
 */

#ifndef CALLBACK_HPP
#define CALLBACK_HPP

#include <string>

#include "bitabstractarchivehandler.hpp"
#include "internal/guids.hpp"

#include <Common/MyCom.h>

constexpr auto kPasswordNotDefined = "Password is not defined";
constexpr auto kEmptyFileAlias     = BIT7Z_STRING( "[Content]");

namespace bit7z {
    class Callback : protected CMyUnknownImp {
        public:
            Callback( const Callback& ) = delete;

            Callback( Callback&& ) = delete;

            Callback& operator=( const Callback& ) = delete;

            Callback& operator=( Callback&& ) = delete;

            virtual ~Callback() = default;

            virtual void throwException( HRESULT error );

        protected:
            explicit Callback( const BitAbstractArchiveHandler& handler ); // Abstract class

            const BitAbstractArchiveHandler& mHandler;
            const char* mErrorMessage;

    };
}
#endif // CALLBACK_HPP
