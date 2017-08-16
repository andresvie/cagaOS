define hook-quit
    set confirm off
end
symbol-file /Users/lordoftherootland/workspace/cagaOS/kernel.sym
set disassembly-flavor intel
break kmain
target remote localhost:1234
continue
