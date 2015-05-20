
var $ = {};

(function (object) {
  "use strict";
  // attr, html, class
  function Decorator(obj) {
    // assign obj to state variable
    this.state = obj;

    // wrap adding event listener
    this.on = function (value, callback) {
      obj.addEventListener(value, callback);      // $.id("main").on("click", function(){alert(123)});
      return this;
    };

    // return value of class attribute
    this.getClass = function () {
      return obj.className;
    };

    // add class to object
    this.addClass = function (value) {
      obj.addClass(value);
      return this;
    };

    // remove subquery in string
    this.removeClass = function(value) {
      obj.className = obj.className
        .replace(new RegExp(' ?\\b' + value + '\\b'), '');
      return this;
    };

    // get or set attribute
    this.attr = function (name, value) {
      var attr = obj.getAttribute(name);

      if(value === undefined) {
        return attr;
      } else {
        obj.setAttribute(name, value);
      }
      return this;
    };

    // fire event
    this.trigger = function (name) {
      var event = new Event(name);
      obj.dispatchEvent(event);
      return this;
    };

    // change html
    this.html = function (value) {
      if(value === undefined) {
        return obj.innerHTML;
      } else {
        obj.innerHTML = value;
      }
      return this;
    };

    // change css
    this.css = function (name, value) {
      if(value === undefined) {
        return obj.style[name];
      } else {
        obj.style[name] = value;
      }
      return this;
    };
  }

  object.id = function (a) {
    var element = document.getElementById(a);
    return new Decorator(element);
  };

  object.decorate = function (element) {
    return new Decorator(element);
  };

  object.fn = {
    hide: function (obj) {
      obj.css("display", "none");
      return obj;
    },
    show: function (obj) {
      obj.css("display", "block");
      return obj;
    }
  };
  return object;
})($);
