/*
 * A simple utility for exporting svg images as bmp images.
 * This then makes 'save as...' BMP.
 *
 * Authors:
 *   Rikhard Prydii <idsgpr@gmail.com>
 *
 * Copyright (C) 2014 Authors
 *
 * Released under GNU GPL, read the file 'COPYING' for more information
 */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <glib/gstdio.h>

#include "bmp-out.h"
#include "cairo-png-out.h"	
#include "extension/system.h"
#include "extension/output.h"

#include <Magick++.h>

namespace Inkscape {
namespace Extension {
namespace Internal {

bool BmpOutput::check(Inkscape::Extension::Extension * /*module*/)
{
    return true;
}

/**
    \brief  This function calls the output module with the filename
	\param  mod   unused
	\param  doc   Document to be saved
    \param  uri   Filename to save to (probably will end in .bmp)
*/
void BmpOutput::save(Inkscape::Extension::Output * mod, SPDocument *doc, gchar const *filename)
{
	gchar *tmpfile = g_build_filename( g_get_tmp_dir(), "inkscape-bmp-export-mediator", NULL );
 	CairoRendererOutput png_out;
	png_out.save(mod, doc, tmpfile);
	try {
		Magick::Image img;
		img.magick("png");
		img.read(tmpfile);
		img.magick("bmp");
		img.write(filename);
	} catch (Magick::Exception &e) {
	    g_unlink(tmpfile); // delete the temporary file
	    g_free(tmpfile);		
		throw Inkscape::Extension::Output::save_failed();		
	}
    g_unlink(tmpfile); // delete the temporary file
    g_free(tmpfile);	
}

/**
	\brief   A function allocate a copy of this function.

	This is the definition of bmp out.  This function just
	calls the extension system with the memory allocated XML that
	describes the data.
*/
void
BmpOutput::init (void)
{
	Inkscape::Extension::build_from_mem(
		"<inkscape-extension xmlns=\"" INKSCAPE_EXTENSION_URI "\">\n"
			"<name>BMP Output</name>\n"
			"<id>rikhard.inkscape.output.bmp.cairo</id>\n"
			"<output>\n"
				"<extension>.bmp</extension>\n"
                "<mimetype>image/bmp</mimetype>\n"
				"<filetypename>Bitmap image (*.bmp)</filetypename>\n"
				"<filetypetooltip>BMP File</filetypetooltip>\n"
			"</output>\n"
		"</inkscape-extension>", new BmpOutput());

	return;
}

} } }  /* namespace Inkscape, Extension, Implementation */

