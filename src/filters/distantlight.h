#ifndef SP_FEDISTANTLIGHT_H_SEEN
#define SP_FEDISTANTLIGHT_H_SEEN

/** \file
 * SVG <filter> implementation, see sp-filter.cpp.
 */
/*
 * Authors:
 *   Hugo Rodrigues <haa.rodrigues@gmail.com>
 *   Niko Kiirala <niko@kiirala.com>
 *   Jean-Rene Reinhard <jr@komite.net>
 *
 * Copyright (C) 2006,2007 Authors
 *
 * Released under GNU GPL, read the file 'COPYING' for more information
 */

#include "sp-object.h"

#define SP_TYPE_FEDISTANTLIGHT (sp_fedistantlight_get_type())
#define SP_FEDISTANTLIGHT(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), SP_TYPE_FEDISTANTLIGHT, SPFeDistantLight))
#define SP_FEDISTANTLIGHT_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST((klass), SP_TYPE_FEDISTANTLIGHT, SPFeDistantLightClass))
#define SP_IS_FEDISTANTLIGHT(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj), SP_TYPE_FEDISTANTLIGHT))
#define SP_IS_FEDISTANTLIGHT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE((klass), SP_TYPE_FEDISTANTLIGHT))

/* Distant light class */

class CFeDistantLight;

class SPFeDistantLight : public SPObject {
public:
	CFeDistantLight* cfedistantlight;

    /** azimuth attribute */
    gfloat azimuth;
    guint azimuth_set : 1;
    /** elevation attribute */
    gfloat elevation;
    guint elevation_set : 1;
};

class CFeDistantLight : public CObject {
public:
	CFeDistantLight(SPFeDistantLight* distantlight);
	virtual ~CFeDistantLight();

	virtual void onBuild(SPDocument* doc, Inkscape::XML::Node* repr);
	virtual void onRelease();

	virtual void onSet(unsigned int key, const gchar* value);

	virtual void onUpdate(SPCtx* ctx, unsigned int flags);

	virtual Inkscape::XML::Node* onWrite(Inkscape::XML::Document* doc, Inkscape::XML::Node* repr, guint flags);

private:
	SPFeDistantLight* spfedistantlight;
};

struct SPFeDistantLightClass {
    SPObjectClass parent_class;
};

GType
sp_fedistantlight_get_type();
#endif /* !SP_FEDISTANTLIGHT_H_SEEN */

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
