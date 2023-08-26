import dash
from dash import html, dcc, callback, Output
import plotly.express as px

dash.register_page(__name__, path='/')

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

Products = ["CurrentAccounts"]

#tables = show_tables()
#tables["row_count"] = [get_table_row_count(t) for t in Products]
#print(get_table_row_count("Accounts"))

data_rows = pd.DataFrame()
data_rows["name"] = Products
data_rows["row_count"] = [get_table_row_count(t) for t in Products]




def serve_layout():
    
    graph = dcc.Graph(id='bar_plot',figure=px.bar(data_rows, x="name", y="row_count",labels={'name':'Products','row_count':'Number'}))
    
    layout = html.Div(children=[
        html.Div(children=[
            html.H1(children='Welcome to this Dash-Board',className="sub-header-title"),
        ], className="home-sub-title " ),
        
            html.Div(children=[
                html.Div(children = [
                    html.Div(children=[
                        html.Div(children=html.H2(children='Number of total accounts'),className="Tnumber-title"),
                        html.H1(children='{}'.format(get_table_row_count("Accounts")),className="Tnumber")
                    ], className="Tnumber-innnerbox"),
                ], className="Tnumber-box"),
                html.Div(children=[
                    html.Div(children=[
                        html.Div(children=html.H2(children='Breakdown of Products'),className="plot-title"),
                        graph,
                    ],className="plot-innerbox")
                ], className="-box"),
                ], className="row"),
        html.Div(children=[], className="home-footer"),
        ],
    )
    return layout

layout = serve_layout
