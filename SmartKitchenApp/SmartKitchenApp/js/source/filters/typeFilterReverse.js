angular.module('typeFilterReverse', []).filter('typeFilterReverse', function ($filter) {
    return function (input) {
        switch (input) {
            case 0: return {int:0, String:"Test1"}; break;
            case 1: return {int:1, String:"Test2"}; break;
            case 2: return {int:2, String:"Test3"}; break;
            case 3: return {int:3, String:"Test4"}; break;
        }
    };
});