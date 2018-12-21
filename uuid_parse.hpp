//-------------------------------------------------------------------------------------------------------
// constexpr GUID parsing
// Written by Alexander Bessonov
// Written by Tobias Loew
//
// Licensed under the MIT license.
//-------------------------------------------------------------------------------------------------------

#pragma once
#include <boost/uuid/uuid.hpp>
#include "guid_parse.hpp"


namespace guid_parse
{
	namespace details {

		template<typename T>
		constexpr uint8_t get_nth_byte_of(T data, size_t pos) {
			return ((uint8_t)((data >> (8 * pos)) & 0xff));
		}

		constexpr boost::uuids::uuid uuid_creator(GUID guid) {
			return 
				boost::uuids::uuid
			{ get_nth_byte_of(guid.Data1, 3), get_nth_byte_of(guid.Data1, 2), get_nth_byte_of(guid.Data1, 1), get_nth_byte_of(guid.Data1, 0)
				, get_nth_byte_of(guid.Data2, 1), get_nth_byte_of(guid.Data2, 0)
				, get_nth_byte_of(guid.Data3, 1), get_nth_byte_of(guid.Data3, 0)
				, guid.Data4[0], guid.Data4[1],guid.Data4[2],guid.Data4[3],guid.Data4[4],guid.Data4[5],guid.Data4[6],guid.Data4[7]
			};
		}

		constexpr boost::uuids::uuid make_uuid_helper(const char *str, size_t N)
		{
			using namespace std::string_literals;
			using namespace details;

			return
				uuid_creator(
				(!(N == long_guid_form_length || N == short_guid_form_length))
				? throw std::domain_error{ "String GUID of the form {XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX} or XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX is expected"s }
				: (N == long_guid_form_length && (str[0] != '{' || str[long_guid_form_length - 1] != '}'))
				? throw std::domain_error{ "Missing opening or closing brace"s }

			: parse_guid(str + (N == long_guid_form_length ? 1 : 0))
					);
		}

		template<size_t N>
		constexpr boost::uuids::uuid make_uuid(const char(&str)[N])
		{
			return make_uuid_helper(str, N - 1);
		}
	}
	
	using details::make_uuid;

	namespace literals
	{
		constexpr boost::uuids::uuid operator "" _uuid(const char *str, size_t N)
		{
			using namespace details;
			return make_uuid_helper(str, N);
		}
	}
}


