# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information
import os,sys
project_root = os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))
bindings_path = os.path.join(project_root, 'build', 'python3.10_release')
sys.path.insert(0, bindings_path)
project = 'Haiku-PyAPI'
copyright = '2025, coolcoder613eb, Zardshard, Fabio Tomat'
author = 'Fabio Tomat'
release = '0.4'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration
extensions = [
    'sphinx.ext.autodoc',   # ESSENZIALE per documentare codice Python (incluso pybind11)
    'sphinx.ext.viewcode',  # Aggiunge i link al codice sorgente (molto utile)
    'sphinxcontrib.htmlhelp', # Aggiunto perché è un'estensione contrib installata (S)
]
templates_path = ['_templates']
exclude_patterns = []
language = 'en' 


# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = 'sphinx_rtd_theme'
html_static_path = ['_static']
autodoc_default_options = {
    'members': True,
    'undoc-members': True,
    'private-members': False,
    'show-inheritance': True,
}
add_module_names = False
autodoc_typehints = "none"