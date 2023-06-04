The arduino communicates with a stockfish engine in a python environment.
This program uses the Stockfish 15.1 windows executable as a UCI for the
python-chess library. 

(Windows)
1. Create virtual environment and activate it

```sh
py -m venv venv
source venv/scripts/activate
```

2. Install dependencies
```sh
py -m pip install -r requirements.txt
```

3. Set the following environment variables in a .env file
- STOCKFISH_LOCATION

4. Run the script
```sh
py src/main.py
```

