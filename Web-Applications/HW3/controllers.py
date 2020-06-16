"""
This file defines actions, i.e. functions the URLs are mapped into
The @action(path) decorator exposed the function at URL:

    http://127.0.0.1:8000/{app_name}/{path}

If app_name == '_default' then simply

    http://127.0.0.1:8000/{path}

If path == 'index' it can be omitted:

    http://127.0.0.1:8000/

The path follows the bottlepy syntax.

@action.uses('generic.html')  indicates that the action uses the generic.html template
@action.uses(session)         indicates that the action uses the session
@action.uses(db)              indicates that the action uses the db
@action.uses(T)               indicates that the action uses the i18n & pluralization
@action.uses(auth.user)       indicates that the action requires a logged in user
@action.uses(auth)            indicates that the action requires the auth object

session, db, T, auth, and tempates are examples of Fixtures.
Warning: Fixtures MUST be declared with @action.uses({fixtures}) else your app will result in undefined behavior
"""

import uuid

from py4web import action, request, abort, redirect, URL, Field
from py4web.utils.form import Form, FormStyleBulma
from py4web.utils.url_signer import URLSigner

from yatl.helpers import A
from . common import db, session, T, cache, auth, signed_url

import logging

# Building a URL Signer
url_signer = URLSigner(session)

@action('index', method='GET')
@action.uses('index.html', session, db)
def view_products():
    # We get all the table rows, via a query.
    rows = db(db.product).select()
    # Displaying the correct ordering
    sort = request.params.get('sort')
    # Displayed in unsorted order
    if(sort == None):
        return dict(rows=rows, sort='unsorted', url_signer=url_signer)
    # Displayed in ascending order
    if(sort == 'asc'):
        asc_order = db().select(db.product.ALL, orderby=db.product.product_cost)
        return dict(rows=asc_order, sort='asc', url_signer=url_signer)
    # Displayed in descending order
    else:
        desc_order = db().select(db.product.ALL, orderby=~db.product.product_cost)
        return dict(rows=desc_order, sort='desc', url_signer=url_signer)

@action('add_product', method=['GET', 'POST'])
@action.uses('product_form.html', session, db)
def add_product():
    form = Form(db.product, csrf_session=session, formstyle=FormStyleBulma)
    if form.accepted:
        # We always want POST requests to be redirected as GETs.
        redirect(URL('index'))
    return dict(form=form)

@action('edit_product/<product_id>', method=['GET', 'POST'])
@action.uses('product_form.html', session, db)
def edit_product(product_id=None):
    """Note that in the above declaration, the product_id argument must match
    the <product_id> argument of the @action."""
    # We read the product.
    p = db.product[product_id]
    if p is None:
        # Nothing to edit.  This should happen only if you tamper manually with the URL.
        redirect(URL('index'))
    form = Form(db.product, record=p, deletable=False, csrf_session=session, formstyle=FormStyleBulma)
    if form.accepted:
        # We always want POST requests to be redirected as GETs.
        redirect(URL('index'))
    return dict(form=form)

@action('delete_product/<product_id>', method='GET')
@action.uses(session, db, url_signer.verify())
def delete(product_id=None):
    p = db.product[product_id]
    if p is not None:
        # Delete row from table
        db(db.product.id == product_id).delete()
    redirect(URL('index'))

