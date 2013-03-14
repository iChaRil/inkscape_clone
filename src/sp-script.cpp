/*
 * SVG <script> implementation
 *
 * Authors:
 *   Felipe Corrêa da Silva Sanches <juca@members.fsf.org>
 *   Jon A. Cruz <jon@joncruz.org>
 *   Abhishek Sharma
 *
 * Copyright (C) 2008 authors
 *
 * Released under GNU GPL version 2 or later, read the file 'COPYING' for more information
 */

#include "sp-script.h"
#include "attributes.h"
#include <cstring>
#include "document.h"

static void sp_script_class_init(SPScriptClass *sc);
static void sp_script_init(SPScript *script);

static void sp_script_release(SPObject *object);
static void sp_script_update(SPObject *object, SPCtx *ctx, guint flags);
static void sp_script_modified(SPObject *object, guint flags);
static void sp_script_set(SPObject *object, unsigned int key, gchar const *value);
static void sp_script_build(SPObject *object, SPDocument *document, Inkscape::XML::Node *repr);
static Inkscape::XML::Node *sp_script_write(SPObject *object, Inkscape::XML::Document *doc, Inkscape::XML::Node *repr, guint flags);

static SPObjectClass *parent_class;

GType sp_script_get_type(void)
{
    static GType script_type = 0;

    if (!script_type) {
        GTypeInfo script_info = {
            sizeof(SPScriptClass),
            NULL,	/* base_init */
            NULL,	/* base_finalize */
            (GClassInitFunc) sp_script_class_init,
            NULL,	/* class_finalize */
            NULL,	/* class_data */
            sizeof(SPScript),
            16,	/* n_preallocs */
            (GInstanceInitFunc) sp_script_init,
            NULL,	/* value_table */
        };
        script_type = g_type_register_static(SP_TYPE_OBJECT, "SPScript", &script_info, (GTypeFlags) 0);
    }

    return script_type;
}

static void sp_script_class_init(SPScriptClass *sc)
{
    parent_class = (SPObjectClass *) g_type_class_ref(SP_TYPE_OBJECT);
    SPObjectClass *sp_object_class = (SPObjectClass *) sc;

    //sp_object_class->build = sp_script_build;
    sp_object_class->release = sp_script_release;
    sp_object_class->update = sp_script_update;
    sp_object_class->modified = sp_script_modified;
    sp_object_class->write = sp_script_write;
    sp_object_class->set = sp_script_set;
}

CScript::CScript(SPScript* script) : CObject(script) {
	this->spscript = script;
}

CScript::~CScript() {
}

static void sp_script_init(SPScript *script)
{
	script->cscript = new CScript(script);
	script->cobject = script->cscript;
}

void CScript::onBuild(SPDocument* doc, Inkscape::XML::Node* repr) {
	SPScript* object = this->spscript;

    CObject::onBuild(doc, repr);

    //Read values of key attributes from XML nodes into object.
    object->readAttr( "xlink:href" );

    doc->addResource("script", object);
}

/**
 * Reads the Inkscape::XML::Node, and initializes SPScript variables.  For this to get called,
 * our name must be associated with a repr via "sp_object_type_register".  Best done through
 * sp-object-repr.cpp's repr_name_entries array.
 */
static void
sp_script_build(SPObject *object, SPDocument *document, Inkscape::XML::Node *repr)
{
	((SPScript*)object)->cscript->onBuild(document, repr);
}

void CScript::onRelease() {
	SPScript* object = this->spscript;

    if (object->document) {
        // Unregister ourselves
        object->document->removeResource("script", object);
    }

    CObject::onRelease();
}

static void sp_script_release(SPObject *object)
{
	((SPScript*)object)->cscript->onRelease();
}

void CScript::onUpdate(SPCtx* ctx, unsigned int flags) {

}

static void sp_script_update(SPObject */*object*/, SPCtx */*ctx*/, guint /*flags*/)
{
}

void CScript::onModified(unsigned int flags) {

}

static void sp_script_modified(SPObject */*object*/, guint /*flags*/)
{
}

void CScript::onSet(unsigned int key, const gchar* value) {
	SPScript* object = this->spscript;

    SPScript *scr = SP_SCRIPT(object);

    switch (key) {
	case SP_ATTR_XLINK_HREF:
            if (scr->xlinkhref) g_free(scr->xlinkhref);
            scr->xlinkhref = g_strdup(value);
            object->requestDisplayUpdate(SP_OBJECT_MODIFIED_FLAG);
            break;
	default:
            CObject::onSet(key, value);
            break;
    }
}

static void
sp_script_set(SPObject *object, unsigned int key, gchar const *value)
{
	((SPScript*)object)->cscript->onSet(key, value);
}

Inkscape::XML::Node* CScript::onWrite(Inkscape::XML::Document* doc, Inkscape::XML::Node* repr, guint flags) {
	return repr;
}

static Inkscape::XML::Node *sp_script_write(SPObject *object, Inkscape::XML::Document *xml_doc, Inkscape::XML::Node *repr, guint flags)
{
/*
TODO:
 code copied from sp-defs
 decide what to do here!

    if (flags & SP_OBJECT_WRITE_BUILD) {

        if (!repr) {
            repr = xml_doc->createElement("svg:script");
        }

        GSList *l = NULL;
        for ( SPObject *child = object->firstChild() ; child; child = child->getNext() ) {
            Inkscape::XML::Node *crepr = child->updateRepr(xml_doc, NULL, flags);
            if (crepr) {
                l = g_slist_prepend(l, crepr);
            }
        }

        while (l) {
            repr->addChild((Inkscape::XML::Node *) l->data, NULL);
            Inkscape::GC::release((Inkscape::XML::Node *) l->data);
            l = g_slist_remove(l, l->data);
        }

    } else {
        for ( SPObject *child = object->firstChild() ; child; child = child->getNext() ) {
            child->updateRepr(flags);
        }
    }

    if (((SPObjectClass *) (parent_class))->write) {
        (* ((SPObjectClass *) (parent_class))->write)(object, xml_doc, repr, flags);
    }
*/

	return ((SPScript*)object)->cscript->onWrite(xml_doc, repr, flags);
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
// vim: filetype=cpp:expandtab:shiftwidth=4:tabstop=8:softtabstop=4 :
