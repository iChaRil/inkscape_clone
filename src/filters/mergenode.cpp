/** \file
 * feMergeNode implementation. A feMergeNode contains the name of one
 * input image for feMerge.
 */
/*
 * Authors:
 *   Kees Cook <kees@outflux.net>
 *   Niko Kiirala <niko@kiirala.com>
 *   Abhishek Sharma
 *
 * Copyright (C) 2004,2007 authors
 *
 * Released under GNU GPL, read the file 'COPYING' for more information
 */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "attributes.h"
#include "xml/repr.h"
#include "filters/mergenode.h"
#include "filters/merge.h"
#include "display/nr-filter-types.h"

#include "sp-factory.h"

namespace {
	SPObject* createMergeNode() {
		return new SPFeMergeNode();
	}

	bool mergeNodeRegistered = SPFactory::instance().registerObject("svg:feMergeNode", createMergeNode);
}

SPFeMergeNode::SPFeMergeNode() : SPObject(), CObject(this) {
	delete this->cobject;
	this->cobject = this;

    this->input = Inkscape::Filters::NR_FILTER_SLOT_NOT_SET;
}

SPFeMergeNode::~SPFeMergeNode() {
}

/**
 * Reads the Inkscape::XML::Node, and initializes SPFeMergeNode variables.  For this to get called,
 * our name must be associated with a repr via "sp_object_type_register".  Best done through
 * sp-object-repr.cpp's repr_name_entries array.
 */
void SPFeMergeNode::build(SPDocument *document, Inkscape::XML::Node *repr) {
	SPFeMergeNode* object = this;
	object->readAttr( "in" );
}

/**
 * Drops any allocated memory.
 */
void SPFeMergeNode::release() {
	CObject::release();
}

/**
 * Sets a specific value in the SPFeMergeNode.
 */
void SPFeMergeNode::set(unsigned int key, gchar const *value) {
	SPFeMergeNode* object = this;
    SPFeMergeNode *feMergeNode = SP_FEMERGENODE(object);
    SPFeMerge *parent = SP_FEMERGE(object->parent);

    if (key == SP_ATTR_IN) {
        int input = sp_filter_primitive_read_in(parent, value);
        if (input != feMergeNode->input) {
            feMergeNode->input = input;
            object->requestModified(SP_OBJECT_MODIFIED_FLAG);
        }
    }

    /* See if any parents need this value. */
    CObject::set(key, value);
}

/**
 * Receives update notifications.
 */
void SPFeMergeNode::update(SPCtx *ctx, guint flags) {
	SPFeMergeNode* object = this;
    //SPFeMergeNode *feMergeNode = SP_FEMERGENODE(object);

    if (flags & SP_OBJECT_MODIFIED_FLAG) {
        object->parent->requestModified(SP_OBJECT_MODIFIED_FLAG);
    }

    CObject::update(ctx, flags);
}

/**
 * Writes its settings to an incoming repr object, if any.
 */
Inkscape::XML::Node* SPFeMergeNode::write(Inkscape::XML::Document *doc, Inkscape::XML::Node *repr, guint flags) {
	SPFeMergeNode* object = this;
    //SPFeMergeNode *feMergeNode = SP_FEMERGENODE(object);

    // Inkscape-only object, not copied during an "plain SVG" dump:
    if (flags & SP_OBJECT_WRITE_EXT) {
        if (repr) {
            // is this sane?
            //repr->mergeFrom(object->getRepr(), "id");
        } else {
            repr = object->getRepr()->duplicate(doc);
        }
    }

    CObject::write(doc, repr, flags);

    return repr;
}


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
