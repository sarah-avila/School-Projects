"""
This file defines the database models
"""
import datetime

from . common import db, Field, auth
from pydal.validators import *

### Define your table below
#
# db.define_table('thing', Field('name'))
#
## always commit your models to avoid problems later
#
# db.commit()
#

def get_user_email():
     return auth.current_user.get('email')
     
db.define_table(
    'phone_numbers',
    Field('phone_number')
)

db.define_table(
    'address_book',
    Field('user_email', default=get_user_email),
    Field('first_name'),
    Field('last_name'),
    Field('phone_numbers', 'reference phone_numbers')
)

# We do not want these fields to appear in forms by default.
db.address_book.id.readable = False
db.address_book.user_email.readable = False

db.commit()
