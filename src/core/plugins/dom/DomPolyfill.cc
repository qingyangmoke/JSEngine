#include "DomPolyfill.h"
void injectDomPolyfill(JSEngineNS::EngineScope *scope)
{
    scope->evaluateJavaScript("(()=>{\"use strict\";const t=function(){function t(){}return t.sendCommand=function(e,n,o){return console.log(\"sendCommand command=\"+e,JSON.stringify(n),typeof window.__module__),window.__module__&&window.__module__.invokeModule(t.MODULE_NAME,e,n,o)},t.toast=function(e,n){void 0===n&&(n=2e3),t.sendCommand(t.TOAST,{message:e,duration:n})},t.MODULE_NAME=\"UI\",t.SET_STYLE=\"setStyle\",t.CREATE_ELEMENT=\"createElement\",t.SET_ATTRIBUTE=\"setAttribute\",t.REMOVE_ATTRIBUTE=\"removeAttribute\",t.INSERT_CHILD=\"insertChild\",t.REMOVE_CHILD=\"removeChild\",t.REPLACE_CHILD=\"replaceChild\",t.TOAST=\"toast\",t.ALERT=\"alert\",t}();var e={class:\"className\"};const n=function(){function n(t){this._element=t,this._attributes=Object.create(null)}return Object.defineProperty(n.prototype,\"uniqueId\",{get:function(){return this._element.uniqueId},enumerable:!1,configurable:!0}),Object.defineProperty(n.prototype,\"keys\",{get:function(){return Object.keys(this._attributes)},enumerable:!1,configurable:!0}),n.prototype._keyModify=function(t){return e[t]||t},n.prototype.getAttribute=function(t){return t=this[this._keyModify(t)],this._attributes[t]},n.prototype.setAttribute=function(e,n){var o;e=this._keyModify(e),this._attributes[e]=n,t.sendCommand(t.SET_ATTRIBUTE,{uniqueId:this.uniqueId,attribute:(o={},o[e]=n,o)})},n.prototype.removeAttribute=function(e){e=this._keyModify(e),Object.hasOwnProperty.call(this,e)&&delete this[e],t.sendCommand(t.REMOVE_ATTRIBUTE,{uniqueId:this.uniqueId,key:e})},n.prototype.toString=function(){var t=this;return Object.keys(this._attributes).map((function(e){return e+'=\"'+t._attributes[e]+'\" '}))},n}();var o=100;const r=function(){function t(e,n){this._nodeType=t.ELEMENT_NODE,this._nodeName=e,this._nodeType=n,this._uniqueId=o++}return Object.defineProperty(t.prototype,\"nodeName\",{get:function(){return this._nodeName},enumerable:!1,configurable:!0}),Object.defineProperty(t.prototype,\"nodeType\",{get:function(){return this._nodeType},enumerable:!1,configurable:!0}),Object.defineProperty(t.prototype,\"uniqueId\",{get:function(){return this._uniqueId},enumerable:!1,configurable:!0}),Object.defineProperty(t.prototype,\"baseURI\",{get:function(){return\"\"},enumerable:!1,configurable:!0}),t.ATTRIBUTE_NODE=2,t.CDATA_SECTION_NODE=4,t.COMMENT_NODE=8,t.DOCUMENT_FRAGMENT_NODE=11,t.DOCUMENT_NODE=9,t.DOCUMENT_POSITION_CONTAINED_BY=16,t.DOCUMENT_POSITION_CONTAINS=8,t.DOCUMENT_POSITION_DISCONNECTED=1,t.DOCUMENT_POSITION_FOLLOWING=4,t.DOCUMENT_POSITION_IMPLEMENTATION_SPECIFIC=32,t.DOCUMENT_POSITION_PRECEDING=2,t.DOCUMENT_TYPE_NODE=10,t.ELEMENT_NODE=1,t.ENTITY_NODE=6,t.ENTITY_REFERENCE_NODE=5,t.NOTATION_NODE=12,t.PROCESSING_INSTRUCTION_NODE=7,t.TEXT_NODE=3,t}();var i=function(){return(i=Object.assign||function(t){for(var e,n=1,o=arguments.length;n<o;n++)for(var r in e=arguments[n])Object.prototype.hasOwnProperty.call(e,r)&&(t[r]=e[r]);return t}).apply(this,arguments)},u=Symbol(\"proxy\");const s=function(){function e(t){this._style={},this._element=t,this._proxyStyle({})}return Object.defineProperty(e.prototype,\"style\",{get:function(){return this._style},set:function(e){this._proxyStyle(i({},e)),t.sendCommand(t.SET_STYLE,{uniqueId:this.uniqueId,style:this.style,replace:1})},enumerable:!1,configurable:!0}),Object.defineProperty(e.prototype,\"uniqueId\",{get:function(){return this._element.uniqueId},enumerable:!1,configurable:!0}),e.prototype._proxyStyle=function(e){if(!this._style[u]){var n=this.uniqueId;this._style=new Proxy(e,{defineProperty:function(t,e,n){return!1},deleteProperty:function(e,o){return delete e[o],\"symbol\"!=typeof o&&t.sendCommand(t.SET_STYLE,{uniqueId:n,style:e,replace:1}),!0},set:function(e,o,r,i){return e[o]=r,\"symbol\"!=typeof o&&t.sendCommand(t.SET_STYLE,{uniqueId:n,style:{prop:r}}),!0}}),this._style[u]=!0}},e.prototype.toString=function(){var t=this;return Object.keys(this._style).map((function(e){return e+\"=\"+t._style[e]+\";\"}))},e}();var c,a=(c=function(t,e){return(c=Object.setPrototypeOf||{__proto__:[]}instanceof Array&&function(t,e){t.__proto__=e}||function(t,e){for(var n in e)Object.prototype.hasOwnProperty.call(e,n)&&(t[n]=e[n])})(t,e)},function(t,e){if(\"function\"!=typeof e&&null!==e)throw new TypeError(\"Class extends value \"+String(e)+\" is not a constructor or null\");function n(){this.constructor=t}c(t,e),t.prototype=null===e?Object.create(e):(n.prototype=e.prototype,new n)}),l=\"id\";const p=function(e){function o(o,i){void 0===i&&(i=r.ELEMENT_NODE);var u=e.call(this,o,i)||this;return u._style=new s(u),u._attributes=new n(u),t.sendCommand(t.CREATE_ELEMENT,{uniqueId:u.uniqueId,tagName:o}),u}return a(o,e),Object.defineProperty(o.prototype,\"previousSibling\",{get:function(){return this._previousSibling},set:function(t){this._previousSibling=t},enumerable:!1,configurable:!0}),Object.defineProperty(o.prototype,\"nextSibling\",{get:function(){return this._nextSibling},set:function(t){this._nextSibling=t},enumerable:!1,configurable:!0}),Object.defineProperty(o.prototype,\"childNodes\",{get:function(){return[]},enumerable:!1,configurable:!0}),Object.defineProperty(o.prototype,\"parentNode\",{get:function(){return this._parent},set:function(t){this._parent=t},enumerable:!1,configurable:!0}),Object.defineProperty(o.prototype,\"style\",{get:function(){return this._style.style},set:function(t){this._style.style=t},enumerable:!1,configurable:!0}),Object.defineProperty(o.prototype,\"parentElement\",{get:function(){return this.parentNode},enumerable:!1,configurable:!0}),Object.defineProperty(o.prototype,\"tagName\",{get:function(){return this._nodeName},enumerable:!1,configurable:!0}),Object.defineProperty(o.prototype,\"textContent\",{get:function(){return\"\"},enumerable:!1,configurable:!0}),Object.defineProperty(o.prototype,\"innerText\",{get:function(){return\"\"},enumerable:!1,configurable:!0}),Object.defineProperty(o.prototype,\"innerHTML\",{get:function(){return\"<\"+this.tagName+\" \"+this._attributes.toString()+' style=\"'+this._style.toString()+'\"></'+this.tagName+\">\"},enumerable:!1,configurable:!0}),Object.defineProperty(o.prototype,\"ownerDocument\",{get:function(){return this._doc},set:function(t){this._doc=t},enumerable:!1,configurable:!0}),Object.defineProperty(o.prototype,\"isConnected\",{get:function(){return null!==this.parentNode},enumerable:!1,configurable:!0}),Object.defineProperty(o.prototype,\"id\",{get:function(){return this.getAttribute(l)},set:function(t){this.setAttribute(l,t)},enumerable:!1,configurable:!0}),Object.defineProperty(o.prototype,\"className\",{get:function(){return this.getAttribute(\"className\")},set:function(t){this.setAttribute(l,t)},enumerable:!1,configurable:!0}),o.prototype.defineAttribute=function(t){var e=this;(\"string\"==typeof t?[t]:t).forEach((function(t){Object.defineProperty(e,t,{get:function(){return e.getAttribute(t)},set:function(n){e.setAttribute(t,n)}})}))},o.prototype.getAttribute=function(t){return this._attributes.getAttribute(t)},o.prototype.setAttribute=function(t,e){this._attributes.setAttribute(t,e)},o.prototype.removeAttribute=function(t){this._attributes.removeAttribute(t)},o.prototype.cloneNode=function(t){void 0===t&&(t=!1);var e=new o(this.tagName,this.nodeType);return e.ownerDocument=this.ownerDocument,e},o.prototype.receiveCommand=function(t,e){\"function\"==typeof this[t]&&this[t](e),console.log(\"command=\",t,\",args=\",e)},o}(r);var f=function(){var t=function(e,n){return(t=Object.setPrototypeOf||{__proto__:[]}instanceof Array&&function(t,e){t.__proto__=e}||function(t,e){for(var n in e)Object.prototype.hasOwnProperty.call(e,n)&&(t[n]=e[n])})(e,n)};return function(e,n){if(\"function\"!=typeof n&&null!==n)throw new TypeError(\"Class extends value \"+String(n)+\" is not a constructor or null\");function o(){this.constructor=e}t(e,n),e.prototype=null===n?Object.create(n):(o.prototype=n.prototype,new o)}}();const h=function(e){function n(t,n){return void 0===n&&(n=r.ELEMENT_NODE),e.call(this,t,n)||this}return f(n,e),Object.defineProperty(n.prototype,\"childNodes\",{get:function(){for(var t=[],e=this.firstChild;e;)t.push(e),e=e.nextSibling;return t},enumerable:!1,configurable:!0}),Object.defineProperty(n.prototype,\"firstChild\",{get:function(){return this._firstChild},enumerable:!1,configurable:!0}),Object.defineProperty(n.prototype,\"lastChild\",{get:function(){return this._lastChild},enumerable:!1,configurable:!0}),n.prototype.iteratorChild=function(t,e){for(var n=t.firstChild;n;){if(e(n))return!0;if(!0===this.iteratorChild(n,e))return!0;n=n.nextSibling}return!1},n.prototype.getElementsByClassName=function(t){var e=[];return this.iteratorChild(this,(function(n){return n.className===t&&e.push(n),!1})),e},n.prototype.getElementsByTagName=function(t){var e=[];return this.iteratorChild(this,(function(n){return n.nodeName===t&&e.push(n),!1})),e},n.prototype.appendChild=function(e){var n;return this._lastChild?(this._lastChild.nextSibling=e,e.previousSibling=this._lastChild,e.nextSibling=null):(this._firstChild=e,this._lastChild=e,this._firstChild.previousSibling=null,this._firstChild.nextSibling=null),e.ownerDocument=this._doc,e.parentNode=this,t.sendCommand(t.INSERT_CHILD,{uniqueId:this.uniqueId,newChild:{uniqueId:e.uniqueId},refChild:{uniqueId:(null===(n=this.lastChild)||void 0===n?void 0:n.uniqueId)||\"\"}}),e},n.prototype.contains=function(t){for(var e=!1,n=this._firstChild;n;)if(n===t){e=!0;break}return e},n.prototype.copyNodeWidthoutChild=function(t){var e=new p(t.nodeName,t.nodeType);return e.ownerDocument=t.ownerDocument,e},n.prototype.cloneNode=function(t){void 0===t&&(t=!1);var e=this.copyNodeWidthoutChild(this);if(t){if(this._firstChild){e._firstChild=this.copyNodeWidthoutChild(this.firstChild),e._lastChild=this._firstChild;for(var n=this._firstChild.nextSibling,o=e._firstChild;n;)o.nextSibling=this.copyNodeWidthoutChild(n),e._lastChild=o.nextSibling,n=n.nextSibling}}else e._firstChild=this._firstChild,e._lastChild=this._lastChild;return e},n.prototype.insertBefore=function(e,n){return n?(e.nextSibling=n.nextSibling,e.previousSibling=n,e.ownerDocument=this.ownerDocument,n.nextSibling=e,e.parentNode=this):this.appendChild(e),t.sendCommand(t.INSERT_CHILD,{uniqueId:this.uniqueId,newChild:{uniqueId:e.uniqueId},refChild:{uniqueId:(null==n?void 0:n.uniqueId)||\"\"}}),e},n.prototype._removeFromChainTree=function(t){t.previousSibling?(t.previousSibling.nextSibling=t.nextSibling,t===this._lastChild&&(this._lastChild=t.previousSibling)):t.nextSibling&&(t.nextSibling.previousSibling=null,t===this._firstChild&&(this._firstChild=t.nextSibling)),t.nextSibling=null,t.previousSibling=null},n.prototype.removeChild=function(e){return this._removeFromChainTree(e),e.parentNode=null,t.sendCommand(t.REMOVE_CHILD,{uniqueId:this.uniqueId,oldChild:{uniqueId:e.uniqueId}}),e},n.prototype.replaceChild=function(e,n){return e.parentNode===this&&this._removeFromChainTree(e),e.previousSibling=n.previousSibling,e.nextSibling=n.nextSibling,e.parentNode=this,e.ownerDocument=this.ownerDocument,t.sendCommand(t.REPLACE_CHILD,{uniqueId:this.uniqueId,newChild:{uniqueId:e.uniqueId},oldChild:{uniqueId:n.uniqueId}}),e},n}(p);var d=function(){var t=function(e,n){return(t=Object.setPrototypeOf||{__proto__:[]}instanceof Array&&function(t,e){t.__proto__=e}||function(t,e){for(var n in e)Object.prototype.hasOwnProperty.call(e,n)&&(t[n]=e[n])})(e,n)};return function(e,n){if(\"function\"!=typeof n&&null!==n)throw new TypeError(\"Class extends value \"+String(n)+\" is not a constructor or null\");function o(){this.constructor=e}t(e,n),e.prototype=null===n?Object.create(n):(o.prototype=n.prototype,new o)}}();const m=function(t){function e(){return t.call(this,\"body\",r.ELEMENT_NODE)||this}return d(e,t),Object.defineProperty(e.prototype,\"uniqueId\",{get:function(){return 1},enumerable:!1,configurable:!0}),e}(h);var y=function(){var t=function(e,n){return(t=Object.setPrototypeOf||{__proto__:[]}instanceof Array&&function(t,e){t.__proto__=e}||function(t,e){for(var n in e)Object.prototype.hasOwnProperty.call(e,n)&&(t[n]=e[n])})(e,n)};return function(e,n){if(\"function\"!=typeof n&&null!==n)throw new TypeError(\"Class extends value \"+String(n)+\" is not a constructor or null\");function o(){this.constructor=e}t(e,n),e.prototype=null===n?Object.create(n):(o.prototype=n.prototype,new o)}}();const _=function(t){function e(){return t.call(this,e.TAG,r.ELEMENT_NODE)||this}return y(e,t),e.TAG=\"div\",e}(h);var b=function(){var t=function(e,n){return(t=Object.setPrototypeOf||{__proto__:[]}instanceof Array&&function(t,e){t.__proto__=e}||function(t,e){for(var n in e)Object.prototype.hasOwnProperty.call(e,n)&&(t[n]=e[n])})(e,n)};return function(e,n){if(\"function\"!=typeof n&&null!==n)throw new TypeError(\"Class extends value \"+String(n)+\" is not a constructor or null\");function o(){this.constructor=e}t(e,n),e.prototype=null===n?Object.create(n):(o.prototype=n.prototype,new o)}}();const g=function(t){function e(n,o){var i=t.call(this,e.TAG,r.ELEMENT_NODE)||this;return(n||0===n)&&i.setAttribute(\"width\",n),(o||0===o)&&i.setAttribute(\"height\",o),i}return b(e,t),e.prototype.receiveCommand=function(e,n){t.prototype.receiveCommand.call(this,e,n)},e.prototype.onLoad=function(t){},e.TAG=\"img\",e}(p);var C=function(){function t(t,e,n,o){this.r=0,this.g=0,this.b=0,this.a=255,this.setRgba(t,e,n,o)}return t.prototype.setRgba=function(t,e,n,o){this.r=t,this.g=e,this.b=n,this.a=o},t.prototype.setColor=function(t){if(/^(rgba|RGBA)/.test(t)){if(4!==(e=t.replace(/(?:\\(|\\)|rgba|RGBA)*/g,\"\").split(\",\")).length)throw new Error(\"invalid color\");this.r=Number(e[0])||0,this.g=Number(e[1])||0,this.b=Number(e[2])||0,this.a=void 0===e[3]?255:Math.min(255,Math.round(255*Number(e[3])))}else if(/^(rgb|RGB)/.test(t)){var e;if(3!==(e=t.replace(/(?:\\(|\\)|rgb|RGB)*/g,\"\").split(\",\")).length)throw new Error(\"invalid color\");this.r=Number(e[0])||0,this.g=Number(e[1])||0,this.b=Number(e[2])||0,this.a=255}else{if(0!==t.indexOf(\"#\"))throw new Error(\"invalid color\");var n=t.substring(1).split(\"\");if(8===n.length)this.a=parseInt(\"\"+n[0]+n[1],16),this.r=parseInt(\"\"+n[2]+n[3],16),this.g=parseInt(\"\"+n[4]+n[5],16),this.b=parseInt(\"\"+n[6]+n[7],16);else if(6===n.length)this.r=parseInt(\"\"+n[0]+n[1],16),this.g=parseInt(\"\"+n[2]+n[3],16),this.b=parseInt(\"\"+n[4]+n[5],16),this.a=255;else{if(3!==n.length)throw new Error(\"invalid color\");this.r=parseInt(\"\"+n[0]+n[0],16),this.g=parseInt(\"\"+n[1]+n[1],16),this.b=parseInt(\"\"+n[2]+n[2],16),this.a=255}}},t.prototype.toString=function(){return\"rgba(\"+this.r+\",\"+this.g+\",\"+this.b+\",\"+this.a/255+\")\"},t}();const O=function(){function t(t){this._lineWidth=1,this._lineCap=\"butt\",this._lineJoin=\"bevel\",this._miterLimit=10,this._lineDashOffset=0,this._antiAlias=!0,this._fillStyle=new C(0,0,0,255),this._strokeStyle=new C(0,0,0,255),this._canvas=t,this.cmd.createContext(\"2d\")}return Object.defineProperty(t.prototype,\"canvas\",{get:function(){return this._canvas},enumerable:!1,configurable:!0}),Object.defineProperty(t.prototype,\"cmd\",{get:function(){return this.canvas.commander},enumerable:!1,configurable:!0}),Object.defineProperty(t.prototype,\"lineWidth\",{get:function(){return this._lineWidth},set:function(t){this._lineWidth=t,this.cmd.pushCommand(\"lineWidth\",{value:t})},enumerable:!1,configurable:!0}),Object.defineProperty(t.prototype,\"lineCap\",{get:function(){return this._lineCap},set:function(t){this._lineCap=t,this.cmd.pushCommand(\"lineCap\",{value:t})},enumerable:!1,configurable:!0}),Object.defineProperty(t.prototype,\"lineJoin\",{get:function(){return this._lineJoin},set:function(t){this._lineJoin=t,this.cmd.pushCommand(\"lineJoin\",{value:t})},enumerable:!1,configurable:!0}),Object.defineProperty(t.prototype,\"miterLimit\",{get:function(){return this._miterLimit},set:function(t){this._miterLimit=t,this.cmd.pushCommand(\"miterLimit\",{value:t})},enumerable:!1,configurable:!0}),Object.defineProperty(t.prototype,\"lineDashOffset\",{get:function(){return this._lineDashOffset},set:function(t){this._lineDashOffset=t,this.cmd.pushCommand(\"lineDashOffset\",{value:t})},enumerable:!1,configurable:!0}),Object.defineProperty(t.prototype,\"antiAlias\",{get:function(){return this._antiAlias},set:function(t){this._antiAlias=t,this.cmd.pushCommand(\"antiAlias\",{value:t?1:0})},enumerable:!1,configurable:!0}),Object.defineProperty(t.prototype,\"fillStyle\",{get:function(){return this._fillStyle.toString()},set:function(t){this._fillStyle.setColor(t),this.cmd.pushCommand(\"fillStyle\",{r:this._fillStyle.r,g:this._fillStyle.g,b:this._fillStyle.b,a:this._fillStyle.a})},enumerable:!1,configurable:!0}),Object.defineProperty(t.prototype,\"strokeStyle\",{get:function(){return this._strokeStyle.toString()},set:function(t){this._strokeStyle.setColor(t),this.cmd.pushCommand(\"strokeStyle\",{r:this._strokeStyle.r,g:this._strokeStyle.g,b:this._strokeStyle.b,a:this._strokeStyle.a})},enumerable:!1,configurable:!0}),t.prototype.setAntiAlias=function(t){this.antiAlias=t},t.prototype.save=function(){this.cmd.pushCommand(\"save\")},t.prototype.restore=function(){this.cmd.pushCommand(\"restore\")},t.prototype.scale=function(t,e){this.cmd.pushCommand(\"scale\",{x:t,y:e})},t.prototype.rotate=function(t){this.cmd.pushCommand(\"rotate\",{angle:t})},t.prototype.translate=function(t,e){this.cmd.pushCommand(\"translate\",{x:t,y:e})},t.prototype.transform=function(t,e,n,o,r,i){this.cmd.pushCommand(\"transform\",{a:t,b:e,c:n,d:o,e:r,f:i})},t.prototype.setTransform=function(t,e,n,o,r,i){this.cmd.pushCommand(\"setTransform\",{a:t,b:e,c:n,d:o,e:r,f:i})},t.prototype.clearRect=function(t,e,n,o){this.cmd.pushCommand(\"clearRect\",{x:t,y:e,w:n,h:o})},t.prototype.fillRect=function(t,e,n,o){this.cmd.pushCommand(\"fillRect\",{x:t,y:e,w:n,h:o})},t.prototype.strokeRect=function(t,e,n,o){this.cmd.pushCommand(\"strokeRect\",{x:t,y:e,w:n,h:o})},t.prototype.beginPath=function(){this.cmd.pushCommand(\"beginPath\")},t.prototype.fill=function(){this.cmd.pushCommand(\"fill\")},t.prototype.stroke=function(){this.cmd.pushCommand(\"stroke\")},t.prototype.drawFocusIfNeeded=function(t){},t.prototype.clip=function(){this.cmd.pushCommand(\"clip\")},t.prototype.isPointInPath=function(t,e){return!1},t.prototype.moveTo=function(t,e){this.cmd.pushCommand(\"moveTo\",{x:t,y:e})},t.prototype.lineTo=function(t,e){this.cmd.pushCommand(\"lineTo\",{x:t,y:e})},t.prototype.quadraticCurveTo=function(t,e,n,o){this.cmd.pushCommand(\"quadraticCurveTo\",{cpx:t,cpy:e,x:n,y:o})},t.prototype.bezierCurveTo=function(t,e,n,o,r,i){this.cmd.pushCommand(\"bezierCurveTo\",{cp1x:t,cp1y:e,cp2x:n,cp2y:o,x:r,y:i})},t.prototype.arcTo=function(t,e,n,o,r){this.cmd.pushCommand(\"arcTo\",{x1:t,y1:e,x2:n,y2:o,radius:r})},t.prototype.rect=function(t,e,n,o){this.cmd.pushCommand(\"rect\",{x:t,y:e,w:n,h:o})},t.prototype.arc=function(t,e,n,o,r,i){void 0===i&&(i=!1),this.cmd.pushCommand(\"arc\",{x:t,y:e,radius:n,startAngle:o,endAngle:r,counterclockwise:i})},t.prototype.closePath=function(){this.cmd.pushCommand(\"closePath\")},t.prototype.fillText=function(t,e,n,o){this.cmd.pushCommand(\"fillText\",{text:t,x:e,y:n,maxWidth:o})},t.prototype.strokeText=function(t,e,n,o){this.cmd.pushCommand(\"strokeText\",{text:t,x:e,y:n,maxWidth:o})},t.prototype.measureText=function(t){return this.cmd.measureText(t)},t.prototype.setLineDash=function(t){this._lineDash=t,this.cmd.pushCommand(\"lineDash\",{lineDash:t})},t.prototype.getLineDash=function(){return this._lineDash},t.prototype.drawImage=function(t){for(var e=[],n=1;n<arguments.length;n++)e[n-1]=arguments[n];if(2===e.length)e[0],e[1];else if(4===e.length)e[0],e[1],e[2],e[3];else{if(8!==e.length)throw new Error(\"参数错误\");e[0],e[1],e[2],e[3],e[4],e[5],e[6],e[7]}this.cmd.pushCommand(\"drawImage\",{textureId:0,params:e})},t.prototype.createLinearGradient=function(t,e,n,o){throw new Error(\"Not support\")},t.prototype.createRadialGradient=function(t,e,n,o,r,i){throw new Error(\"Not support\")},t.prototype.createPattern=function(t,e){throw void 0===e&&(e=\"repeat\"),new Error(\"Not support\")},t.prototype.createImageData=function(t,e){throw new Error(\"Not support\")},t.prototype.getImageData=function(t,e,n,o){throw new Error(\"Not support\")},t.prototype.putImageData=function(t,e,n,o,r,i,u){throw new Error(\"Not support\")},t}(),E=function(){function t(t){this._w=t}return Object.defineProperty(t.prototype,\"width\",{get:function(){return this._w},enumerable:!1,configurable:!0}),t}(),v=function(){function t(t){this._commands=[],this._canvas=t}return t.prototype.pushCommand=function(t,e){this._commands.push({command:t,data:e})},t.prototype._args=function(t){return void 0===t&&(t={}),t.uniqueId=this._canvas.uniqueId,t},t.prototype.createContext=function(e){this.sendCommand(t.CREATE_CONTEXT_COMMAND,{type:e})},t.prototype.measureText=function(e){var n=this.sendCommand(t.MEASURE_TEXT_COMMAND,{text:e}),o=JSON.parse(n);return new E(o.width)},t.prototype.sendCommand=function(e,n,o){return window.__module__&&window.__module__.invokeModule(t.MODULE_NAME,e,this._args(n||{}),o)},t.prototype.flush=function(){this.sendCommand(t.BATCH_COMMAND,{commands:this._commands,length:this._commands.length}),this._commands=[]},t.prototype.render=function(){this._commands.length>0&&this.flush()},t.MODULE_NAME=\"canvas\",t.BATCH_COMMAND=\"batchCmd\",t.MEASURE_TEXT_COMMAND=\"measureText\",t.CREATE_CONTEXT_COMMAND=\"createContext\",t}();var N=function(){var t=function(e,n){return(t=Object.setPrototypeOf||{__proto__:[]}instanceof Array&&function(t,e){t.__proto__=e}||function(t,e){for(var n in e)Object.prototype.hasOwnProperty.call(e,n)&&(t[n]=e[n])})(e,n)};return function(e,n){if(\"function\"!=typeof n&&null!==n)throw new TypeError(\"Class extends value \"+String(n)+\" is not a constructor or null\");function o(){this.constructor=e}t(e,n),e.prototype=null===n?Object.create(n):(o.prototype=n.prototype,new o)}}();const T=function(t){function e(){var n=t.call(this,e.TAG)||this;return n._command=new v(n),n}return N(e,t),Object.defineProperty(e.prototype,\"commander\",{get:function(){return this._command},enumerable:!1,configurable:!0}),e.prototype.getContext=function(t){if(!t.match(/2d/i))throw new Error(\"invalid arguments\");return this._context||(this._context=new O(this)),this._context},e.TAG=\"canvas\",e}(p),I=new(function(){function t(){this._map=new Map,this.registerElement(_.TAG,_),this.registerElement(g.TAG,g),this.registerElement(T.TAG,T)}return t.prototype.registerElement=function(t,e){this._map.set(t,e)},t.prototype.createElement=function(t){return this._map.has(t)?new(this._map.get(t))(t):new h(t,r.ELEMENT_NODE)},t}());var w=function(){var t=function(e,n){return(t=Object.setPrototypeOf||{__proto__:[]}instanceof Array&&function(t,e){t.__proto__=e}||function(t,e){for(var n in e)Object.prototype.hasOwnProperty.call(e,n)&&(t[n]=e[n])})(e,n)};return function(e,n){if(\"function\"!=typeof n&&null!==n)throw new TypeError(\"Class extends value \"+String(n)+\" is not a constructor or null\");function o(){this.constructor=e}t(e,n),e.prototype=null===n?Object.create(n):(o.prototype=n.prototype,new o)}}();const S=new(function(t){function e(){var e=t.call(this,\"document\",r.DOCUMENT_NODE)||this;return e._body=new m,e.defineAttribute([\"title\"]),e}return w(e,t),Object.defineProperty(e.prototype,\"uniqueId\",{get:function(){return 0},enumerable:!1,configurable:!0}),Object.defineProperty(e.prototype,\"body\",{get:function(){return this._body},enumerable:!1,configurable:!0}),e.prototype.createElement=function(t){return I.createElement(t)},e.prototype.registerElement=function(t,e){I.registerElement(t,e)},e.prototype.getElementById=function(t){var e;return this.iteratorChild(this,(function(n){if(n.id===t)return e=n,!0})),e},e}(h)),A=new(function(){function t(){}return t.prototype.setItem=function(t,e){},t.prototype.getItem=function(t){},t.prototype.removeItem=function(t){},t.prototype.clear=function(){},t}()),D=new(function(){function t(){}return t.prototype.setItem=function(t,e){},t.prototype.getItem=function(t){},t.prototype.removeItem=function(t){},t.prototype.clear=function(){},t}()),M=new(function(){function t(){}return Object.defineProperty(t.prototype,\"userAgent\",{get:function(){return\"Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.101 Safari/537.36\"},enumerable:!1,configurable:!0}),t}());function P(t,e){window[t]=e}const x=new(function(){function t(){this._callbackIds=0,this._callbackMap=new Map}return Object.defineProperty(t.prototype,\"contextId\",{get:function(){return window.contextId},enumerable:!1,configurable:!0}),t.prototype.makeNativeCallID=function(t){var e=this._callbackIds++;return this._callbackMap.set(e,t),e},t.prototype.queryNativeCallID=function(t,e){if(void 0===e&&(e=!1),this._callbackMap.has(t))return this._callbackMap.get(t)},t.prototype.deleteNativeCallID=function(t){this._callbackMap.delete(t)},t.prototype.invokeNativeModule=function(t,e,n,o){return window.__module__&&window.__module__.invokeModule(t,e,n,o)},t}()),j=function(){function t(t){this._moduleName=t}return Object.defineProperty(t.prototype,\"moduleName\",{get:function(){return this._moduleName},enumerable:!1,configurable:!0}),t}();var k=function(){var t=function(e,n){return(t=Object.setPrototypeOf||{__proto__:[]}instanceof Array&&function(t,e){t.__proto__=e}||function(t,e){for(var n in e)Object.prototype.hasOwnProperty.call(e,n)&&(t[n]=e[n])})(e,n)};return function(e,n){if(\"function\"!=typeof n&&null!==n)throw new TypeError(\"Class extends value \"+String(n)+\" is not a constructor or null\");function o(){this.constructor=e}t(e,n),e.prototype=null===n?Object.create(n):(o.prototype=n.prototype,new o)}}(),q=\"setTimeout\",L=\"setInterval\",R=\"JSMTimer\",U=\"JSMTimer\";const G=function(t){function e(){return t.call(this,U)||this}return k(e,t),e.setTimeout=function(t,e){if(!t)return-1;var n=x.makeNativeCallID({moduleName:U,type:q,callback:t});return x.invokeNativeModule(R,q,{id:n,delay:e}),n},e.clearTimeout=function(t){var e=x.queryNativeCallID(t);e&&e.moduleName===U&&e.type===q&&x.deleteNativeCallID(t),x.invokeNativeModule(R,\"clearTimeout\",{id:t})},e.setInterval=function(t,e){if(!t)return-1;var n=x.makeNativeCallID({moduleName:U,type:L,callback:t});return x.invokeNativeModule(R,L,{id:n,interval:e}),n},e.clearInterval=function(t){var e=x.queryNativeCallID(t);e&&e.moduleName===U&&e.type===L&&(x.deleteNativeCallID(t),x.invokeNativeModule(R,\"clearInterval\",{id:t}))},e.prototype.timerCallback=function(t){console.log(\"timerCallback\",t);var e=JSON.parse(t),n=x.queryNativeCallID(e.id);n&&n.moduleName===U?(n.callback(),n.type===q&&x.deleteNativeCallID(e.id)):console.log(\"timerCallback not found\",t,JSON.stringify(n))},e}(j),B=new(function(){function t(){this._moduleMap=new Map,this.registerJSModule(new G)}return t.prototype.registerJSModule=function(t){if(window[t.moduleName])throw new Error(\"module [\"+t.moduleName+\"] exists\");this._moduleMap[t.moduleName]=t,P(t.moduleName,t)},t}());P(\"document\",S),P(\"navigator\",M),P(\"memoryStorage\",D),P(\"localStorage\",A),P(\"setTimeout\",G.setTimeout),P(\"setInterval\",G.setInterval),P(\"clearInterval\",G.clearInterval),P(\"clearTimeout\",G.clearTimeout),P(\"JSModule\",j),P(\"registerJSModule\",(function(t){B.registerJSModule(t)}))})();", "internal://polyfill", 0);
}