

# Javascript prototype chaining

written by 오영택

> javascript를 하면서 가장 햇갈리는 것이 바로 prototype형 객체지향일 것 이다. 부족하지만 내가 이해한 방식대로 이 개념을 정리해본다


### prototype chain은 왜 나왔는가

일단 기존의 class base OOP의 특징을 잘 살펴보자.

```python
class Me: 
    def __init__(self,name,age):#constructor
        self.name = name#property
        self.age = age 
    def introduce(self):#method
        print "my name is",self.name
        print "i am",self.age,"years old"

class Brother(Me):#inherit
    def introduce(self):#method override
        print "i am brother"

youngtaek = Me('oyt',26) #object(instance)
youngtaek.introduce()
'''
my name is oyt
 i am 26 years old 
 '''

chanhyuk = Brother('och',25)
chanhyuk.introduce()
'''
i am brother
'''

```

python을 통해 간단히 기존 언어의 oop를 복습해봤다. 여기서 알 수 있듯, class based oop에서 object는 철저히 class에서 설계된 대로 기능한다. 즉, 위의 예제에서 youngtake object에 내가 다니는 학교에 대한 정보를 넣고 싶다면 class를 수정한 후, 다시 instance로 만들어야 한다. 

만약 brother뿐 아니라, sister, mother,father등을 만들려면 계속 subclass를 만들어야 한다. 게다가 특정 object의 속성(property나 method)등을 바꾸고 싶으면, 애초에 class를 다시 만들어서 재할당 해야 하는 단점이 있다.

**즉 class based oop에서는 객체의 특징을 바꾸려면 class전체를 다시 뜯어 고친다음, 기존의 객체는 무시하고 다시 새로운 겍체를 만들어줘야 하는 불편함이 있다.**

#### 그렇다면 prototype chaining에서는 이것을 어떻게 개선하는가

```javascript
function Me(name,age) { //function(emulate class)
	this.name = name //constructor
	this.age = age
}

function Brother(name,age) {
	Me.call(this,name,age) //inherit
}

youngtaek = new Me('oytt',26) // object
// define method(!?) after class(?!)
Me.prototype.introduce = function ()  {
	console.log(`my name is ${this.name}`)
	console.log(`i am ${this.age} years old`)
}
// change property after instanted!!
youngtaek.name = 'oyt'
youngtaek.introduce()

`
my name is oyt
i am 26 years old
`

chanhyuk = new Brother('och',25)
Brother.prototype.introduce = function () {
	console.log('i am brother')
}
chanhyuk.introduce()
`
i am brother
`

```

여기서 주목할 점은 class 대신 함수가 있고, class 역할을 하는 함수는 바꾸지도 않았는데 method를 마음대로 추가할 수 있고 심지어 instance화 된 후에 property조차 바꾸는 유연함이다.

여기서 용어 정리를 확실히 하고 넘어가자. **javascript에서는 class가 없다.** ecmascript 6에 class라는 용어가 나오지만, syntactic sugar일 뿐 실제로 class based oop에서 뜻하는 class가 아니다(콘솔에서 찍어 보면 알겠지만, class 키워드로 class를 만들어도 실제로 만들어지는건 함수이다).

그리고 더욱 중요한 것은, **method도 없다.** javascript에서 object는 key-value로 된 변수이고 이는 JSON이라는 표기법으로 나타낸다. value에는 어떤 형태의 object이든 들어갈 수 있고 **따라서 value의 형태가 함수라고 method라는 거창한 용어를 붙여줄 필요가 없다.** javascript에서 함수는 constructor를 가지고 있는 object일 뿐이다(이걸 유식한 말로, function as first class citizen[(링크)](https://en.wikipedia.org/wiki/First-class_function)이라고 한다).


### 어떤 마법이 일어난 것일까?

javascript에서 new 연산자로 object를 만드는 순간, object는 함수의 prototype를 가리키는 **prototype link**를 생성한다. 즉, 위의 예에서 youngtaek 이라는 object는 Me라는 함수의 prototype를 항상 주시하고 있다.

자 이제, youngtaek.introduce() 라고 입력했을 때에, javascript 안에서 어떠한 일이 일어나고 있는지 살펴보자. 우선, javascript는 youngtaek이라는 object가 introduce라는 key를 가지고 있는지 확인할 것이다. 주지하다시피, youngtake은 name, age 라는 key만 가지고 있다. 그럴 경우 javascript는 **prototype link**를 참조하여 생성했던 함수의 **prototype object**에 introduce라는 key가 있는지 확인한다. 위의 예제에선 비록 생성 후에 추가하였지만, 분명히 Me prototype가 introduce라는 key를 가지고 있기 때문에 해당하는 함수를 실행할 수 있었다. 정리하자면 아래와 같은 과정을 거친 것이다.

>youngtaek.introduce() 
=> youngtaek에 introduce가 있는가?(no)
=> 그렇다면 prototype link가 가르키고 있는 object에는 introduce가 있는가? (yes)
=>  해당 value를 실행.
			
위와 같은 과정을 **prototype chaining** 이라고 한다. 모든 javascript object는 object.prototype를 가지는데 해당값은 null이다. 즉, **prototype chaining**은 object.prototype이 나올 때 까지 계속 해당 key값이 있는지 찾아가는 loop라고 생각하면 된다. 이 과정을 이해하기 위해 예제 코드를 하나 더 가져와본다.

```javascript
function F() {
	this.a = 1
	this.b = 2
}
F.prototype = {b:3,c:4}

var o = new F()
// o = {a:1,b:2}, o.[[prototype]] ={b:3,c:4}
// o.[[prototype]].[[prototype]] = null

// 이 예제에서 오브젝트.[[Prototype]]은 오브젝트의 프로토타입을 의미한다고 생각하자.
// 이건 ECMAScript의 기본 표기법이고 스크립트 내부에서는 사용할 수 없다.

console.log(o.a); // 1
// o는 'a'라는 속성을 가지는가? 그렇다. 1의 값을 가지고 있다.

console.log(o.b); // 2
// o는 'b'라는 속성을 가지는가? 그렇다. 2의 값을 가지고 있다.
// 프로토타입 역시 'b'라는 속성을 가지지만 이 값은 쓰이지 않는다. 이것을 "속성의 가려짐(property shadowing)" 이라고 부른다.

console.log(o.c); // 4
// o는 'c'라는 속성을 가지는가? 아니다. 프로토타입을 확인해보자.
// o.[[Prototype]]은 'c'라는 속성을 가지는가? 가지고 값은 4이다.

console.log(o.d); // undefined
// o는 'd'라는 속성을 가지는가? 아니다. 프로토타입을 확인해보자.
// o.[[Prototype]]은 'd'라는 속성을 가지는가? 아니다. 다시 프로토타입을 확인해보자.
// o.[[Prototype]].[[Prototype]]은 null이다. 찾는 것을 그만두자. 속성이 발견되지 않았기 때문에 undefined를 반환한다.




//credit: mozilla foundation
//url: https://developer.mozilla.org/ko/docs/Web/JavaScript/Guide/Inheritance_and_the_prototype_chain
```

여기서 알 수 있듯, 원래 있는 object의 key를 먼저 참고하고 해당 key가 없을 경우에만 prototype을 참고하며 따라서 prototype과 원래 object에 같은 key가 있다면 object에 있는 key를 먼저 실행한다.

이런 구조 덕에, interitance도 자연스럽게 재현할 수 있다. 나아가 기존의 class oop 보다 훨씬 유연하게 속성을 바꿀 수 있다. 왜냐하면 속성을 추가하는데 순서의 제한이 없고, 객체 자신도 새로운 key:value를 추가할 수 있는만큼 다른 객체에 영향을 주지 않고도 얼마든지 속성을 더 넣을 수 있기 때문이다.