The arduino communicates with a stockfish engine in a python environment.
This program uses the Stockfish 15.1 windows executable as a UCI for the
python-chess library. 

1. Create virtual environment and activate it

```sh
py -m venv venv
source venv/scripts/activate
```

2. Set the following environment variables in a .env file
- STOCKFISH_LOCATION

3. Run the script
```sh
cd backend/src
py main.py
```

