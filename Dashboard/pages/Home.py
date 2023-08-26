import dash
from dash import html, dcc

dash.register_page(__name__, path='/')

import sqlite3
import pandas as pd

db = '../Backend/Bank_v1.db'

def run_query(q):
    with sqlite3.connect(db) as conn:
        return pd.read_sql(q,conn)

def get_table_row_count(tablename):
    q = '''
        SELECT
            COUNT(1)
        FROM %s;
        ''' % tablename
    return run_query(q)["COUNT(1)"][0]



layout = html.Div(children=[
    html.Div(children=[
        html.H1(children='Welcome to this Dash-Board',className="sub-header-title"),
    ], className="home-sub-title " ),
    html.Div(children=[], className="home-footer"),

    html.Div(children = [
        html.Div(children=html.H2(children='Number of total accounts'),className="Tnumber-title"),
        html.H1(children='{}'.format(get_table_row_count("Accounts")),className="Tnumber")
    ]),
    ],
)