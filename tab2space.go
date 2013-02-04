package main

import (
  "os"
  "bytes"
  "io/ioutil"
  "path/filepath"
)

func main(){
  old, replace := []byte{'\t'}, []byte{' ',' '}
  files := []string{}
  for _, name := range os.Args[1:] {
    matches, _ := filepath.Glob(name)
    files = append(files, matches...)
  }
  for _, file := range files {
    if file == "space2tab.go" || file == "tab2space.go" {
      continue
    }
    contents, _ := ioutil.ReadFile(file)
    result := bytes.Replace(contents, old, replace, -1)
    ioutil.WriteFile(file, result, 0644)
  }
}
