# constexpr-GUID-C-11-
constexpr GUID parsing in C++11

inspired by https://gist.github.com/AlexBAV/b58e92d7632bae5d6f5947be455f796f

usage

<code>
constexpr const GUID clsid = guid_parse::make_guid("{EFECF0A1-399E-40B8-A13C-ACE28DB40212}");
</code>

or

<code>
using namespace guid_parse::literals;

constexpr const GUID clsid = "{EFECF0A1-399E-40B8-A13C-ACE28DB40212}"_guid;
</code>
