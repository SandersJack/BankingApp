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

Tables = ["Accounts","CurrentAccounts","SavingsAccounts"]

def serve_layout():

    layout = html.Div(children=[
        dcc.Dropdown(id='DropDown_table',
                options=[
                         {'label': i, 'value': i} for i in Tables
                        ],
               # value=fileNames,
                placeholder='Select a Table',
                multi=False,
                clearable=False
                ),
        html.Div(children=[
            
        ],id='tbl_out')
    ])
    return layout

layout = serve_layout

@callback(
            Output('tbl_out', 'children'), 
            Input('DropDown_table', 'value'))
def update_figure(DropDown_table):
    table = get_table(DropDown_table)
    table_fig = dash_table.DataTable(table.to_dict('records'),[{"name": i, "id": i} for i in table.columns]),
    return table_fig
