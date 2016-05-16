#!/bin/bash

make docs
git subtree push --prefix docs/html origin gh-pages
