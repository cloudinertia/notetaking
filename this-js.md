


# Javascript의 this와 inherit

written by 오영택

> this keyword를 이해하기란 쉽지 않다. 다만 나 나름대로  이해해보려 노력하였고, 아래와 같은 코드를 작성하였다. 더불에 왜 저렇게 나오는지 해석을 달았다. [여기](http://www.nextree.co.kr/p7522/)에서 분류한 this의 종류 중 어떤것에 해당하는지도 밝혔다.
>
>참고: this의 종류(출처:[여기](http://www.nextree.co.kr/p7522/))
>
>1. 기본적으로 전역 객체 참조
>2. 메소드(!?) 안에 있는 this는 불러온 부모 객체 참조
>3. new 로 생성자 함수를 호출할 때, this는 새로 생성한 객체 참조
>4. apply,call,bind시 해당 메소드의 첫번째 인자가 this
>5. prototype의 메소드도 호출한 객체 참고
>6. this는 접근 제어자 역할도 겸함


```javascript
// node's global variables: global, module.exports
this.global = "this is global"// this === module.exports
var _this = this


function A() {
    this.this1 = function() {console.log('this1',this)}
    this.this2 = () => {console.log('this2',this)}
    this.this7 = function() {console.log('this7',this)}.bind(this)
    this.this8 = function() {console.log('this8',this)}.bind(_this)
    this.this9 = {  x: () => console.log('this9.x',this), 
                    y : function (){console.log('this9.y',this)},
                    z : { inner_z1: () => console.log('this9.z.inner_z1',this),
                          inner_z2 : function() { console.log('this9.z.inner_z2',this)},
                          name: 'this is inner z obj'
                    } ,
                    name:'this is this9 inner obj'
                }

    this.this6 = console.log('this6',this) 
    this.this12 = function () {
        console.log('this12',this)
        function innerFunction() {
        console.log('this12 inner',this)
        }
        innerFunction()
    }
}

var this3 = function() {console.log('this3',this)}
var this4 = () => console.log('this4',this)
var this5 = { x:function () {console.log('this5.x',this)}}

A.this3 = this3
A.this4 = this4
A.this5 = this5
A.prototype = {
    this10 : () => console.log('this10',this),
    this11 : function() {console.log('this11',this)},
}
 


var a = new A()

a.name = "this is small a"

a.this1()// small a
a.this2()// small a
//a.this3()
//a.this4()
A.this3() // large A
A.this4() // global (module.exports)
A.this5.x() // {x : Function}
a.this7() // small a
a.this8() // global (module.exports)

a.this9.x() // small a
a.this9.y() // inner this9
a.this9.z.inner_z1() // small a
a.this9.z.inner_z2() // inner z
a.this10() // global(module.exports)
a.this11() // small a
a.this12() // this12: small a, this12 inner: global objects

console.log(this === exports) //true
console.log(this === global) //false
```

- this1: 2번
- this2: 4번( () => 함수는 기본적으로 function(){}.bind(this)와 같음)
- this3: 1번 + 6번. small a는 this3을 볼 수 없다.
- this4: 4번 + 6번
- this5: 2번
- this7: 4번
- this8: 4번. _this는 맨 위에서 주입시켜줬다.
- this9: 
	- this9.x : 4번. small a
	- this9.y : 2번
	- this9.z :
		- inner_z1: 4번
		- inner_z2: 2번
-  this10: 4번
- this11: 5번
- this12: 
	- this12: 2번
	- this12 inner: 1번