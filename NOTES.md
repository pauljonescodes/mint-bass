# Notes

## Thursday, January 4, 2024 2:05:00 PM

```PowerShell
Get-ChildItem -Filter "_ *.wav" | Rename-Item -NewName {$_.Name -replace '^_ '}
```

```PowerShell
Get-ChildItem -Filter "*.wav" | Rename-Item -NewName {"Sample " + $_.Name}
```

- B 5
- E 8 
- A 7
- D 11
- G 6