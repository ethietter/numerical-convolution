
#include "boost/config/warning_disable.hpp"
#include "boost/spirit/include/qi.hpp"
#include "boost/spirit/include/classic.hpp"

#include <iostream>
#include <string>
#include <vector>

template <typename Iterator>
bool parse_numbers(Iterator first, Iterator last)
{
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;
    using qi::char_;
    using qi::double_;
    using qi::phrase_parse;
    using ascii::space;

    bool r = phrase_parse(
            first,
            last,
            double_ >> *(char_('a') >> char_('b') >> double_),
            space
            );
    if(first != last){
        return false;
    }
    return r;
}
