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

#ifndef BITMEMCOMPRESSOR_HPP
#define BITMEMCOMPRESSOR_HPP

#include "bitcompressor.hpp"

namespace bit7z {
    /**
     * @brief Class that allows to compress memory buffers to the filesystem, to standard streams,
     *        or to other memory buffers.
     *
     * It let decide various properties of the produced archive file, such as the password
     * protection and the compression level desired.
     */
    using BitMemCompressor BIT7Z_MAYBE_UNUSED = BitCompressor< const buffer_t >;
}
#endif // BITMEMCOMPRESSOR_HPP
