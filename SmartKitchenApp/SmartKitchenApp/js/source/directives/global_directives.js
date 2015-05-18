app.directive('ngConfirmClick', [
    function () {
        return {
            restrict: 'A',
            link: function (scope, element, attr) {
                var msg = attr.ngConfirmClick || "Ben je zeker?";
                var clickAction = attr.confirmedClick;
                element.bind('click',function (event) {
                    bootbox.confirm(msg, function(result) {
                        if(result == true) {
                            scope.$eval(clickAction);
                        }
                    });
                });
            }
        };
    }]);

app.directive('ngEnter', [
    function () {
        return {
            restrict: 'A',
            link: function (scope, element, attrs) {
                element.bind("keydown keypress", function (event) {
                    if(event.which === 13) {
                        scope.$apply(function (){
                            scope.$eval(attrs.ngEnter);
                        });

                        event.preventDefault();
                    }
                });
            }
        };
    }]);

app.directive('capitalize', function() {
   return {
     require: 'ngModel',
     link: function(scope, element, attrs, modelCtrl) {
        var capitalize = function(inputValue) {
           if(inputValue == undefined) inputValue = '';
           var capitalized = inputValue.toUpperCase();
           if(capitalized !== inputValue) {
              modelCtrl.$setViewValue(capitalized);
              modelCtrl.$render();
            }         
            return capitalized;
         }
         modelCtrl.$parsers.push(capitalize);
         capitalize(scope[attrs.ngModel]);  // capitalize initial value
     }
   };
});

app.directive('noCapitalize', function() {
   return {
     require: 'ngModel',
     link: function(scope, element, attrs, modelCtrl) {
        var nocapitalize = function(inputValue) {
           if(inputValue == undefined) inputValue = '';
           var nocapitalized = inputValue.toLowerCase();
           if(nocapitalized !== inputValue) {
              modelCtrl.$setViewValue(nocapitalized);
              modelCtrl.$render();
            }         
            return nocapitalized;
         }
         modelCtrl.$parsers.push(nocapitalize);
         nocapitalize(scope[attrs.ngModel]);  // nocapitalize initial value
     }
   };
});

app.directive('autoCapitalize', function($parse) {
   return {
     require: 'ngModel',
     link: function(scope, element, attrs, modelCtrl) {
        var capitalize = function(inputValue) {
           if (inputValue === undefined) { inputValue = ''; }
           var capitalized = inputValue.charAt(0).toUpperCase() +
                             inputValue.substring(1);
           if(capitalized !== inputValue) {
              modelCtrl.$setViewValue(capitalized);
              modelCtrl.$render();
            }         
            return capitalized;
         }
         modelCtrl.$parsers.push(capitalize);
         capitalize($parse(attrs.ngModel)(scope)); // capitalize initial value
     }
   };
});
app.directive("ngFileSelect", function () {
    return {
        link: function ($scope, el) {
            el.bind("change", function (e) {
                $scope.file = (e.srcElement || e.target).files[0];
                $scope.getFile();
            });
        }
    }
});

app.directive("passwordVerify", function () {
    return {
        require: "ngModel",
        scope: {
            passwordVerify: '='
        },
        link: function (scope, element, attrs, ctrl) {
            scope.$watch(function () {
                var combined;

                if (scope.passwordVerify || ctrl.$viewValue) {
                    combined = scope.passwordVerify + '_' + ctrl.$viewValue;
                }
                return combined;
            }, function (value) {
                if (value) {
                    ctrl.$parsers.unshift(function (viewValue) {
                        var origin = scope.passwordVerify;
                        if (origin !== viewValue) {
                            ctrl.$setValidity("passwordVerify", false);
                            return undefined;
                        } else {
                            ctrl.$setValidity("passwordVerify", true);
                            return viewValue;
                        }
                    });
                }
            });
        }
    };
});

app.directive('angularMask', function() {
    return {
        restrict : 'A',
        link: function($scope, el, attrs) {
            var format = attrs.angularMask,
                arrFormat = format.split('|');

            if(arrFormat.length > 1){
                arrFormat.sort(function(a, b){
                    return a.length - b.length;
                });
            }
            function mask(o) {
                var value = o.value.replace(/\D/g,'');
                if(arrFormat.length > 1){
                    for(var a in arrFormat){
                        if(value.replace(/\D/g,'').length <= arrFormat[a].replace(/\D/g,'').length){
                            format = arrFormat[a];
                            break;
                        }
                    }
                }
                var newValue = '';
                for(var nmI = 0, mI = 0; mI < format.length;){
                    if(format[mI].match(/\D/)){
                        newValue+=format[mI];
                    }else{
                        if(value[nmI] != undefined){
                            newValue+=value[nmI];
                            nmI++;
                        }else{
                            break;
                        }
                    }
                    mI++;
                }
                o.value = newValue;
            }
            el.bind('keyup keydown', function(e) {
                var keyList = [8,37,39,46];
                if(keyList.indexOf(e.keyCode) == -1)mask(this);
            });
        }
    };
});