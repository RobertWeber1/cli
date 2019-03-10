#pragma once
#include "layout/layout_object.h"
#include "util/line.h"
#include <tr1/functional>
#include <set>
#include <list>

namespace CLI
{

namespace widget
{


class TextData
{
public:
	typedef std::tr1::function< void( const TextData & data )> UpdateCallback;
	typedef struct ChangedLine
	{
		ChangedLine( unsigned int index, util::Line const& line )
		: index( index )
		, line( line )
		{}

		bool operator() ( ChangedLine const& lhs, ChangedLine const& rhs) const
  		{
  			return lhs.index < rhs.index;
  		}

		unsigned int index;
		util::Line const& line;
	}ChangedLine;

	void add( unsigned int index, util::Line const& line );
	void reomve_line( unsigned int index );
	void clear();

	std::set<ChangedLine> const& changed_lines();
	void clear_changed_lines();

private:
	std::set<ChangedLine> _changed_lines;
	std::list<util::Line> _lines;
};


class TextView : public layout::LayoutObject
{

};


} //namespace widget

} //namespace CLI
