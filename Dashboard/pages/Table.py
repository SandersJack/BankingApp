import dash
from dash import html, dcc, callback, Output, dash_table, Input
import plotly.express as px
import dash_bootstrap_components as dbc

dash.register_page(__name__, path='/Table')


import sqlite3
import pandas as pd

db = '../Backend/Bank_v1.db'

def run_query(q):
    with sqlite3.connect(db) as conn:
        return pd.read_sql(q,conn)


def show_tables():
    q = '''
        SELECT
            name
        FROM sqlite_master
        WHERE type IN ("table","view");
        '''
    return run_query(q)

def get_table_row_count(tablename):
    q = '''
        SELECT
            COUNT(1)
        FROM %s;
        ''' % tablename
    return run_query(q)["COUNT(1)"][0]

def sum_column(tablename):
    q = '''
        SELECT
            SUM(VALUE)
        FROM %s;
        ''' % tablename
    return run_query(q)["SUM(VALUE)"][0]

def get_table(tablename):
    q = '''
        SELECT
            * 
        FROM %s;
        ''' % tablename
    return run_query(q)

Products = ["CurrentAccounts"]

def serve_layout():
    table = get_table("Accounts")

    layout = dbc.Container([
    dbc.Label('Click a cell in the table:'),
    dash_table.DataTable(table.to_dict('records'),[{"name": i, "id": i} for i in table.columns], id='tbl'),
    dbc.Alert(id='tbl_out'),
    ])
    return layout

layout = serve_layout

@callback(Output('tbl_out', 'children'), Input('tbl', 'active_cell'))
def update_graphs(active_cell):
    return str(active_cell) if active_cell else "Click the table"