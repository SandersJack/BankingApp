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

def sum_column(tablename):
    q = '''
        SELECT
            SUM(VALUE)
        FROM %s;
        ''' % tablename
    return run_query(q)["SUM(VALUE)"][0]

Products = ["CurrentAccounts"]

def serve_layout():
    
    data_rows = pd.DataFrame()
    data_rows["name"] = Products
    data_rows["row_count"] = [get_table_row_count(t) for t in Products]
    
    
    NAccounts = get_table_row_count("Accounts")
    total_value = 0
    sum_col = [] 
    for i in range(len(Products)):
        sum_col.append(sum_column(Products[i]))
        total_value += sum_col[i]
    TDeposits = total_value
    deposits = pd.DataFrame({"Products":Products,
                    "TValues":sum_col})
    
    graph = dcc.Graph(id='bar_plot',figure=px.bar(data_rows, x="name", y="row_count",labels={'name':'Products','row_count':'Number'}))
    
    figure_dep = px.bar(deposits, x="TValues", color="Products", labels={'TValues':'Total Deposits'}, orientation='h')
    figure_dep.update_layout(yaxis={'visible': False, 'showticklabels': False})
    graph_deposits = dcc.Graph(id='bar_plot_deposits',figure=figure_dep)
    
    layout = html.Div(children=[
        html.Div(children=[
            html.H1(children='Welcome to this Dash-Board',className="sub-header-title"),
        ], className="home-sub-title " ),
        
            html.Div(children=[
                html.Div(children = [
                    html.Div(children=[
                        html.Div(children=html.H2(children='Number of total accounts'),className="Tnumber-title"),
                        html.H1(children='{}'.format(NAccounts),className="Tnumber")
                    ], className="Tnumber-innnerbox"),
                    html.Div(children=[
                        html.Div(children=html.H2(children='Total deposits'),className="Tnumber-title"),
                        html.H1(children='£{:.2f}'.format(TDeposits),className="Tnumber")
                    ], className="Tnumber-innnerbox"),
                    html.Div(children=[
                        graph_deposits
                    ], className="Tnumber-innnerbox")
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
