workflow "Test Library" {
  on = "push"
  resolves = ["Test"]
}

action "Test" {
  uses = "dockcross/linux-x64@latest"
  runs = "make test"
}
