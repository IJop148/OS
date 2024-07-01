global _idt_flush
_idt_flush:
    lidt [esp+4] ; Assume idt_flush is called with 'idt_ptr' as an argument on the stack
    ret