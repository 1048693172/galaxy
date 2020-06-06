#!/usr/bin/python2.5

# Copyright (C) 2010 The Android Open Source Project
# 
# Licensed under the Apache License, Version 2.0 (the "License"); you may not
# use this file except in compliance with the License. You may obtain a copy of
# the License at
# 
# http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
# License for the specific language governing permissions and limitations under
# the License.

"""Represents user's contact information, friends and credentials."""

from google.appengine.ext import db


class User(db.Model):
  """Data model class to hold user objects."""

  handle = db.StringProperty(required=True)
  firstname = db.TextProperty()
  lastname = db.TextProperty()
  status = db.TextProperty()
  phone_home = db.PhoneNumberProperty()
  phone_office = db.PhoneNumberProperty()
  phone_mobile = db.PhoneNumberProperty()
  email = db.EmailProperty()
  deleted = db.BooleanProperty()
  updated = db.DateTimeProperty(auto_now_add=True)

  @classmethod
  def get_user_info(cls, username):
    if username not in (None, ''):
      query = cls.gql('WHERE handle = :1', username)
      return query.get()
    return None

  @classmethod
  def get_user_last_updated(cls, username):
    if username not in (None, ''):
      query = cls.gql('WHERE handle = :1', username)
      return query.get().updated
    return None

  @classmethod
  def get_user_id(cls, username):
    if username not in (None, ''):
      query = cls.gql('WHERE handle = :1', username)
      return query.get().key().id()
    return None

  @classmethod
  def get_user_status(cls, username):
    if username not in (None, ''):
      query = cls.gql('WHERE handle = :1', username)
      return query.get().status
    return None


class UserCredentials(db.Model):
  """Data model class to hold credentials for a Voiper user."""

  username = db.StringProperty(required=True)
  password = db.StringProperty()

  @classmethod
  def get(cls, username):
    if username not in (None, ''):
      query = cls.gql('WHERE username = :1', username)
      return query.get().password
    return None


class UserFriends(db.Model):
  """Data model class to hold user's friendlist info."""

  username = db.StringProperty()
  friend_handle = db.StringProperty(required=True)
  updated = db.DateTimeProperty(auto_now_add=True)
  deleted = db.BooleanProperty()

  @classmethod
  def get_friends(cls, username):
    if username not in (None, ''):
      query = cls.gql('WHERE username = :1', username)
      friends = query.fetch(50)
      return friends
    return None