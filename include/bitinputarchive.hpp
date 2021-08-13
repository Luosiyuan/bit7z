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
#ifndef BITINPUTARCHIVE_HPP
#define BITINPUTARCHIVE_HPP

#include <vector>
#include <string>
#include <cstdint>

#include "bitarchivehandler.hpp"
#include "bitarchiveiteminfo.hpp"
#include "bitarchiveitemoffset.hpp"
#include "bitformat.hpp"
#include "bitpropvariant.hpp"
#include "bittypes.hpp"

struct IInStream;
struct IInArchive;
struct IOutArchive;
struct IArchiveExtractCallback;

namespace bit7z {
    using std::vector;

    class ExtractCallback;

    class BitInputArchive {
        public:
            BitInputArchive( const BitArchiveHandler& handler, tstring in_file );

            BitInputArchive( const BitArchiveHandler& handler, const vector< byte_t >& in_buffer );

            BitInputArchive( const BitArchiveHandler& handler, std::istream& in_stream );

            BitInputArchive( const BitInputArchive& ) = delete;

            BitInputArchive( BitInputArchive&& ) = delete;

            BitInputArchive& operator=( const BitInputArchive& ) = delete;

            BitInputArchive& operator=( BitInputArchive&& ) = delete;

            virtual ~BitInputArchive();

#ifdef BIT7Z_AUTO_FORMAT
            /**
             * @return the detected format of the file.
             */
            BIT7Z_NODISCARD const BitInFormat& detectedFormat() const noexcept;
#endif

            /**
             * @brief Gets the specified archive property.
             *
             * @param property  the property to be retrieved.
             *
             * @return the current value of the archive property or an empty BitPropVariant if no value is specified.
             */
            BIT7Z_NODISCARD BitPropVariant getArchiveProperty(BitProperty property ) const;

            /**
             * @brief Gets the specified property of an item in the archive.
             *
             * @param index     the index (in the archive) of the item.
             * @param property  the property to be retrieved.
             *
             * @return the current value of the item property or an empty BitPropVariant if the item has no value for
             * the property.
             */
            BIT7Z_NODISCARD BitPropVariant getItemProperty(uint32_t index, BitProperty property ) const;

            /**
             * @return the number of items contained in the archive.
             */
            BIT7Z_NODISCARD uint32_t itemsCount() const;

            /**
             * @param index the index of an item in the archive.
             *
             * @return true if and only if the item at index is a folder.
             */
            BIT7Z_NODISCARD bool isItemFolder(uint32_t index ) const;

            /**
             * @param index the index of an item in the archive.
             *
             * @return true if and only if the item at index is encrypted.
             */
            BIT7Z_NODISCARD bool isItemEncrypted(uint32_t index ) const;

            BIT7Z_NODISCARD const tstring& getArchivePath() const noexcept;

            BIT7Z_NODISCARD const BitArchiveHandler& getHandler() const noexcept;

            void extract( const tstring& out_dir, const vector< uint32_t >& indices ) const;

            BIT7Z_NODISCARD vector< byte_t > extract(unsigned int index ) const;

            void extract( std::ostream& out_stream, unsigned int index ) const;

            void extract( map< tstring, vector< byte_t > >& out_map ) const;

            void test() const;

        protected:
            IInArchive* openArchiveStream( const tstring& name, IInStream* in_stream );

            HRESULT initUpdatableArchive( IOutArchive** newArc ) const;

            void extract( const vector< uint32_t >& indices, ExtractCallback* extract_callback ) const;

            void test( ExtractCallback* extract_callback ) const;

            BIT7Z_NODISCARD HRESULT close() const noexcept;

            friend class BitArchiveOpener;

            friend class BitArchiveCreator;

            friend class BitOutputArchive;

        private:
            IInArchive* mInArchive;
#ifdef BIT7Z_AUTO_FORMAT
            const BitInFormat* mDetectedFormat;
#endif
            const BitArchiveHandler& mArchiveHandler;
            const tstring mArchivePath;

        public:
            class const_iterator {
                public:
                    // iterator traits
                    using iterator_category BIT7Z_MAYBE_UNUSED = std::input_iterator_tag;
                    using value_type BIT7Z_MAYBE_UNUSED = BitArchiveItemOffset;
                    using reference = const BitArchiveItemOffset&;
                    using pointer = const BitArchiveItemOffset*;
                    using difference_type BIT7Z_MAYBE_UNUSED = uint32_t; //so that count_if returns a uint32_t

                    const_iterator& operator++() noexcept;

                    const_iterator operator++( int ) noexcept;

                    bool operator==( const const_iterator& other ) const noexcept;

                    bool operator!=( const const_iterator& other ) const noexcept;

                    reference operator*() noexcept;

                    pointer operator->() noexcept;

                private:
                    BitArchiveItemOffset mItemOffset;

                    const_iterator( uint32_t item_index, const BitInputArchive& item_archive ) noexcept;

                    friend class BitInputArchive;
            };

            BIT7Z_NODISCARD const_iterator begin() const noexcept;

            BIT7Z_NODISCARD const_iterator end() const noexcept;

            BIT7Z_NODISCARD const_iterator cbegin() const noexcept;

            BIT7Z_NODISCARD const_iterator cend() const noexcept;

            BIT7Z_NODISCARD const_iterator find(const tstring& path ) const noexcept;

            BIT7Z_NODISCARD bool contains( const tstring& path ) const noexcept;
    };
}

#endif //BITINPUTARCHIVE_HPP
