/***********************************************************************
    filename:   CEGUICentredRenderedString.cpp
    created:    25/05/2009
    author:     Paul Turner
 *************************************************************************/
/***************************************************************************
 *   Copyright (C) 2004 - 2009 Paul D Turner & The CEGUI Development Team
 *
 *   Permission is hereby granted, free of charge, to any person obtaining
 *   a copy of this software and associated documentation files (the
 *   "Software"), to deal in the Software without restriction, including
 *   without limitation the rights to use, copy, modify, merge, publish,
 *   distribute, sublicense, and/or sell copies of the Software, and to
 *   permit persons to whom the Software is furnished to do so, subject to
 *   the following conditions:
 *
 *   The above copyright notice and this permission notice shall be
 *   included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 *   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 *   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 *   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *   OTHER DEALINGS IN THE SOFTWARE.
 ***************************************************************************/
#include "CEGUICentredRenderedString.h"
#include "CEGUIRenderedString.h"
#include "CEGUIVector.h"

// Start of CEGUI namespace section
namespace CEGUI
{
//----------------------------------------------------------------------------//
CentredRenderedString::CentredRenderedString(const RenderedString& string) :
    FormattedRenderedString(string)
{
}

//----------------------------------------------------------------------------//
void CentredRenderedString::format(const Size& area_size)
{
    d_offsets.clear();

    for (size_t i = 0; i < d_renderedString->getLineCount(); ++i)
        d_offsets.push_back(
            (area_size.d_width - d_renderedString->getPixelSize(i).d_width) / 2.0f);
}

//----------------------------------------------------------------------------//
void CentredRenderedString::draw(GeometryBuffer& buffer,
                                 const Vector2& position,
                                 const ColourRect* mod_colours,
                                 const Rect* clip_rect) const
{
    Vector2 draw_pos;
    draw_pos.d_y = position.d_y;

    for (size_t i = 0; i < d_renderedString->getLineCount(); ++i)
    {
        draw_pos.d_x = position.d_x + d_offsets[i];
        d_renderedString->draw(i, buffer, draw_pos, mod_colours, clip_rect, 0.0f);
        draw_pos.d_y += d_renderedString->getPixelSize(i).d_height;
    }
}

//----------------------------------------------------------------------------//
size_t CentredRenderedString::getFormattedLineCount() const
{
    return d_renderedString->getLineCount();
}

//----------------------------------------------------------------------------//
float CentredRenderedString::getHorizontalExtent() const
{
    float w = 0.0f;
    for (size_t i = 0; i < d_renderedString->getLineCount(); ++i)
    {
        const float this_width = d_renderedString->getPixelSize(i).d_width;
        if (this_width > w)
            w = this_width;
    }

    return w;
}

//----------------------------------------------------------------------------//
float CentredRenderedString::getVerticalExtent() const
{
    float h = 0.0f;
    for (size_t i = 0; i < d_renderedString->getLineCount(); ++i)
        h += d_renderedString->getPixelSize(i).d_height;

    return h;
}

//----------------------------------------------------------------------------//
    
} // End of  CEGUI namespace section