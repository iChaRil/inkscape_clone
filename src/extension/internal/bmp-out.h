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

#ifndef EXTENSION_INTERNAL_BMP_OUT_H
#define EXTENSION_INTERNAL_BMP_OUT_H

#include "extension/implementation/implementation.h"

namespace Inkscape {
namespace Extension {
namespace Internal {

class BmpOutput : Inkscape::Extension::Implementation::Implementation {

public:
    bool check(Inkscape::Extension::Extension *module);
    void save(Inkscape::Extension::Output *mod,
              SPDocument *doc,
              gchar const *filename);
    static void init();
};

} } }  /* namespace Inkscape, Extension, Implementation */

#endif /* !EXTENSION_INTERNAL_BMP_OUT_H */

/*
  Local Variables:
  mode:c++
  c-file-style:"stroustrup"
  c-file-offsets:((innamespace . 0)(inline-open . 0)(case-label . +))
  indent-tabs-mode:nil
  fill-column:99
  End:
*/
// vim: filetype=cpp:expandtab:shiftwidth=4:tabstop=8:softtabstop=4:fileencoding=utf-8:textwidth=99 :