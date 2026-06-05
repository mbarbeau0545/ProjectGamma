from app.script_runtime_api import *

log('--- Symbols from ECU .sym ---')
for sym in list_symbols():
    sigs = list_symbol_signals(sym)
    log(f"{sym}: {', '.join(sigs)}")

log('done')
