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

# Building URL signer
url_signer = URLSigner(session)

# The auth.user below forces login.
@action('index')
@action.uses('index.html', auth.user, session, db)
def index():
    rows = db(db.address_book).select()
    # Displaying the current user's address book
    current_address_book = db(db.address_book.user_email == auth.current_user.get('email')).select()
    # Displaying the list of phone numbers
    #TODO - fix displaying phone numbers
    #current_phone_numbers = db(db.phone_numbers.phone_number).select().aslist()
    #for row in current_phone_numbers:
        #string = row.phone_number
        #row["phone_numbers"] = s
        #rows_2 = current_phone_numbers
    return dict(rows=current_address_book, url_signer=url_signer)
    
@action('add_contact', method=['GET', 'POST'])
@action.uses('contact_form.html', session, db)
def add_contact():
    # Create form
    form = Form(db.address_book, csrf_session=session, formstyle=FormStyleBulma)
    if form.accepted:
        redirect(URL('index'))
    # Return the form
    return dict(form=form)
   
@action('edit_contact/<contact_id>', method=['GET', 'POST'])
@action.uses('contact_form.html', session, db)
def edit_contact(contact_id=None):
    p = db.address_book[contact_id]
    if p is None or auth.current_user.get('email') != p.user_email:
        redirect(URL('index'))
    # Create form
    form = Form(db.address_book, record=p, deletable=False, csrf_session=session, formstyle=FormStyleBulma)
    if form.accepted:
        redirect(URL('index'))
    # Return the form
    return dict(form=form)
    
@action('delete_contact/<contact_id>', method='GET')
@action.uses(session, db, url_signer.verify())
def delete_contact(contact_id=None):
    p = db.address_book[contact_id]
    if p is not None:
        # Delete contact from db
        db( (db.address_book.id == contact_id ) & ( db.address_book.user_email == auth.current_user.get('email')) ).delete()
    redirect(URL('index'))







