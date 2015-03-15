var Person = function(fullName, age) {
  var name = fullName.split(" ");
  this.firstName = name[0];
  this.lastName = name.length > 1 ? name[1] : "";
  this.age = age;
}

Person.prototype.setName = function(firstName, lastName){
  this.firstName = firstName;
  this.lastName = lastName;
}

Person.prototype.getName = function(){
  return this.firstName + " " + this.lastName;
}
var a = new Person("Andrew", 23);
console.log(a.getName());
a.setName("Andrew", "Kennedy");
console.log(a.getName());
