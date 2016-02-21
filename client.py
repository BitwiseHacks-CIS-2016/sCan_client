import click

import requests
from clint.textui import prompt


BASE_URL = 'https://blooming-tor-76519.herokuapp.com/_client'
district_list = [
    'Islands', 'Kwai_Tsing', 'North', 'Sai_Kung', 'Sha_Tin', 'Tai_Po', 'Tsuen_Wan',
    'Yuen_Long', 'Kowloon_City', 'Kwun_Tong', 'Sham_Shui_Po', 'Wong_Tai_Sin', 'Yau_Tsim_Mong',
    'Southern', 'Wan_Chai'
]


@click.group('main')
def main():
    pass


@main.command('create')
def create():
    ''' Create a new device and record attributes in database '''
    payload = dict()
    lat = prompt.query('Enter latitude:\n>> ')
    lng = prompt.query('Enter longitude:\n>> ')
    payload['type'] = prompt.options('Enter bin type', options=[
        {'selector': 1, 'prompt': 'paper', 'return': 'paper'},
        {'selector': 2, 'prompt': 'metal', 'return': 'metal'},
        {'selector': 3, 'prompt': 'normal', 'return': 'normal'},
        {'selector': 4, 'prompt': 'plastic', 'return': 'plastic'},
        {'selector': 5, 'prompt': 'glass', 'return': 'glass'},
    ])
    payload['district'] = prompt.options('Enter District',
                                       options=[
                                           {'selector': i, 'prompt': district, 'return': district} for
                                           i, district in enumerate(district_list)
                                       ])
    payload['lat'] = lat if lat[0] != 'n' else '-'+lat[1:]
    payload['lng'] = lng if lng[0] != 'n' else '-'+lng[1:]
    try:
        req = requests.post(BASE_URL, json=payload)
        req.raise_for_status()
        click.echo('Success')
    except requests.exceptions.HTTPError:
        click.echo('Operation Failed')


@main.command('update')
def update_device():
    payload = dict()
    payload['id'] = prompt.query('Enter device ID')
    payload['filled'] = prompt.options('Filled?', options=[
        {'selector': 'Y', 'prompt': 'Yes', 'return': 1},
        {'selector': 'N', 'prompt': 'No', 'return': 0}
    ])
    try:
        req = requests.put(BASE_URL, json=payload)
        req.raise_for_status()
        click.echo('Success')
    except requests.exceptions.HTTPError as e:
        click.echo(e)
        click.echo('Operation Failed')


if __name__ == '__main__':
    main()
